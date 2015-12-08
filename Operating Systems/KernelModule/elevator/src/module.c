#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/timekeeping.h>
#include <linux/kthread.h>
#include <linux/mutex.h>
#include <linux/delay.h>
#include <syscalls.h>
#include <asm-generic/uaccess.h>
#include <stdbool.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Matthew and Jim");
MODULE_DESCRIPTION("Simple module providing a simulation of a functional elevator");

/*Note: The basic proc structure of this implementation
  is heavily based upon code provided by Britton Dennis*/

#define ENTRY_NAME "elevator"
#define PERMS 0644
#define PARENT NULL
#define KFLAGS (__GFP_WAIT | __GFP_IO | __GFP_FS) 
#define NUM_TYPES 4
#define MIN_FLOOR 1
#define MAX_FLOOR 10
#define LOAD_MAX 16
#define PEOPLE_MAX 8
#define IDLE 0
#define STOPPED 4

struct floor_stats{
	int currentWeight;
	int serviceCount;
};


static struct file_operations fops;
static char *message;
static char *state;
static int read_p;
static struct list_head requestList[MAX_FLOOR];
static struct list_head nextStop;
static struct floor_stats stats[MAX_FLOOR];
static struct mutex floor_mutex[MAX_FLOOR];
static struct mutex nextstop_lock;
static struct mutex elevator_lock;
static struct task_struct* elevator_thread;

struct passenger {
	int weight, units, destination;
};
struct list_next {
	struct list_head list;
	int floor;
};

struct list_item {
	struct list_head list;
	struct passenger person;
};


struct mover{
	int state, currentFloor, nextFloor, currentLoad, peopleCount;
	struct list_head list;
} elevator;

void update_elevator(struct list_item* pers);
void unload_elevator(void);
void update_elevator_moving(void);
void update_next_stop(void);

struct passenger get_passenger(int type, int destination) {
	struct passenger p;
	if(type == 0) { /*Adult*/
		p.weight = 2;
		p.units = 1;
	}
	else if(type == 1) { /*Child*/
		p.weight = 1;
		p.units = 1;
	}
	else if(type == 2) { /*Bellhop*/
		p.weight = 4;
		p.units = 2;
	}
	else if(type == 3) { /*Room Service*/
		p.weight = 4;
		p.units = 1;
	}
	p.destination = destination;
	return p;
}

char* get_state(int s) {
	state = kmalloc(sizeof(char) * 8, KFLAGS);
	memset(state, 0, sizeof(char) * 8);
	if(s == 0)
		strcat(state, "IDLE");
	else if(s == 1)
		strcat(state, "UP");
	else if(s == 2)
		strcat(state, "DOWN");
	else if(s == 3)
		strcat(state, "LOADING");
	else if (s == 4)
		strcat(state, "STOPPED");
	else
		strcat(state, "INVALID");
	return state;
}

int elevator_run(void *data){
	while(!kthread_should_stop())
	{
		/* deactivated*/
		if (isActive == false) 
		{
			if (elevator.currentLoad == 0)
				/*deactivated and no people*/
			{
				int ret;
				elevator.state = STOPPED;
				isRunning = false;
				ret = kthread_stop(elevator_thread);
				if (ret != -EINTR)
					printk("elevator thread has stopped\n");
			}
			else
			{
				struct list_item* pers;
				mutex_lock_interruptible(&elevator_lock);
				pers = list_first_entry(&elevator.list, struct list_item, list);
				mutex_unlock(&elevator_lock);
				elevator.nextFloor = pers->person.destination;
				update_next_stop();
				update_elevator_moving();
				unload_elevator();
				elevator.state = 0;
			}
		}
		/*still active*/
		else
		{
			if (!list_empty(&requestList[elevator.currentFloor - 1]))
			{
				struct list_head* floorList, *temp;
				struct list_item* pers;
				if (kthread_should_stop()) break;
				ssleep(1);
				if (kthread_should_stop()) break;
				list_for_each_safe(floorList, temp, &requestList[elevator.currentFloor - 1])
				{
					/*get everyone that elevator holds*/
					if (kthread_should_stop()) break;
					pers = list_entry(floorList, struct list_item, list);
					if (pers->person.weight + elevator.currentLoad < LOAD_MAX && elevator.peopleCount + pers->person.units < PEOPLE_MAX)
					{
						mutex_lock_interruptible(&elevator_lock);
						list_move_tail(&pers->list, &elevator.list);
						mutex_unlock(&elevator_lock);						
						update_elevator(pers);
					}
					else
					{
						break;
					}
				}
				if (!list_empty(&requestList[elevator.currentFloor - 1]))
				{
					/*still people left on floor*/
					struct list_next* addNext = kmalloc(sizeof(struct list_next), KFLAGS);
					addNext->floor = elevator.currentFloor;
					mutex_lock_interruptible(&nextstop_lock);
					list_add_tail(&addNext->list, &nextStop);
					mutex_unlock(&nextstop_lock);
				}
				mutex_lock_interruptible(&elevator_lock);
				pers = list_first_entry(&elevator.list, struct list_item, list);
				mutex_unlock(&elevator_lock);
				elevator.nextFloor = pers->person.destination;
				update_next_stop();
				update_elevator_moving();
				unload_elevator();
				elevator.state = 0;
				
			}
			else if (list_empty(&nextStop))
			{
				/*elevator empty, no waiting*/
				elevator.state = IDLE;
				isRunning = false;
				elevator.nextFloor = elevator.currentFloor;
				if (kthread_should_stop()) break;
				ssleep(1);	
			}
			else
			{	/*list not empty but elevator empty*/
				struct list_next* floorNext;
				mutex_lock_interruptible(&nextstop_lock);
				floorNext = list_first_entry(&nextStop,struct list_next, list);
				mutex_unlock(&nextstop_lock);
				elevator.nextFloor = floorNext->floor;
				update_elevator_moving();
				list_del_init(&floorNext->list);
				kfree(floorNext);
			}
		}
	}
	return true;
}
void update_next_stop(void)
{
	mutex_lock_interruptible(&nextstop_lock);
	if (!list_empty(&nextStop))
	{
		struct list_head* floorList, *temp;
		struct list_next* pers;
		list_for_each_safe(floorList, temp, &nextStop)
		{
			if (kthread_should_stop())
			{
				mutex_unlock(&nextstop_lock);
				return;
			} 
			pers = list_entry(floorList, struct list_next, list);
			if (list_empty(&requestList[pers->floor - 1]))
			{
				list_del(floorList);
				kfree(pers);
			}

		}
	}
	mutex_unlock(&nextstop_lock);
}

void update_elevator_moving(void)
{
	int time, dir = elevator.currentFloor - elevator.nextFloor;
	if (dir > 0)
	{
		elevator.state = 2;
	}
	else if (dir < 0)
	{
		elevator.state = 1;
	}
	else
	{
		elevator.state = 0;
	}
	time = abs(elevator.currentFloor - elevator.nextFloor) * 2;
	printk("traveling from %d to %d, taking %d\n", elevator.currentFloor, elevator.nextFloor, time);
	while (time > 0)
	{
		if (kthread_should_stop()) return;
		ssleep(2);
		if (kthread_should_stop()) return;
		if (dir > 0)
		{
			elevator.currentFloor--;
		}
		else if (dir < 0)
		{
			elevator.currentFloor++;
		}
		time -= 2;
	}
	elevator.currentFloor = elevator.nextFloor;
}
void update_elevator(struct list_item* pers)
{
	isRunning = true;
	printk("adding %d people/%d units from Floor: %d\n",pers->person.weight, pers->person.units, elevator.currentFloor);
	elevator.currentLoad += pers->person.weight;
	elevator.peopleCount += pers->person.units;
	printk("now %d people/%d units from Floor: %d\n",pers->person.weight, pers->person.units, elevator.currentFloor);
	mutex_lock_interruptible(&floor_mutex[elevator.currentFloor - 1]);
	stats[elevator.currentFloor - 1].currentWeight -= pers->person.weight;
	stats[elevator.currentFloor - 1].serviceCount++; 
	mutex_unlock(&floor_mutex[elevator.currentFloor - 1]);
}
void unload_elevator(void)
{
	struct list_head* loadList, *temp;
	struct list_item* pers;
	mutex_lock_interruptible(&elevator_lock);
	list_for_each_safe(loadList, temp, &elevator.list)
	{
		if (kthread_should_stop()) 
		{
			mutex_unlock(&elevator_lock);
			return;
		}
		pers = list_entry(loadList, struct list_item, list);
		if (pers->person.destination == elevator.currentFloor)
		{
			elevator.currentLoad -= pers->person.weight;
			elevator.peopleCount -= pers->person.units; 
			list_del(loadList);
			kfree(pers);
		}
	}
	mutex_unlock(&elevator_lock);
	if (elevator.currentLoad == 0)
	{
		isRunning = false;
	}
}

int elevator_proc_open(struct inode *sp_inode, struct file *sp_file) {
	int i;
	char summary[80];
	state = get_state(elevator.state);	
	read_p = 1;
	message = kmalloc(sizeof(char) * 1000, KFLAGS);
	if (message == NULL) {
		printk("ERROR, timed_proc_open");
		return -ENOMEM;
	}

	memset(message, 0, sizeof(char)*1000);
	memset(summary, 0, sizeof(char)*80);
	strcat(message,"****Elevator****\n");
	sprintf(summary,"State: %s\n", state);
	kfree(state);
	state = NULL;
	strcat(message, summary);
	sprintf(summary,"Current Floor: %d\n", elevator.currentFloor);
	strcat(message, summary);
	sprintf(summary,"Next Floor: %d\n",elevator.nextFloor);
	strcat(message, summary);
	if (elevator.currentLoad % 2 == 0)
	{
		sprintf(summary,"Current Load: %d passengers, %d weight units\n", elevator.peopleCount, elevator.currentLoad / 2);
	}
	else
	{
		sprintf(summary,"Current Load: %d passengers, %d.5 weight units\n", elevator.peopleCount, elevator.currentLoad / 2);
	}
	strcat(message, summary);
	strcat(message, "****Waiting****\n");
	for (i = 0; i < MAX_FLOOR; i++)
	{
		mutex_lock_interruptible(&floor_mutex[i]);
		if (stats[i].currentWeight % 2 == 0)
		{
			sprintf(summary,"Floor %d: Waiting Load: %d, Total Serviced: %d\n",i + 1, stats[i].currentWeight / 2, stats[i].serviceCount);
		}
		else
		{
			sprintf(summary,"Floor %d: Waiting Load: %d.5, Total Serviced: %d\n",i + 1, stats[i].currentWeight / 2, stats[i].serviceCount);
		}
		strcat(message, summary);
		mutex_unlock(&floor_mutex[i]);
	}
	return 0;
}

ssize_t elevator_proc_read(struct file *sp_file, char __user *buf, size_t size, loff_t *offset) {
	int len = strlen(message);
	read_p = !read_p;
	if (read_p) {
		return 0;
	}
	copy_to_user(buf, message, len);

	return len;
}

void activate_elevator(void)
{
	elevator.state = IDLE;
	elevator_thread = kthread_run(elevator_run, NULL, "elevator thread");
	if (IS_ERR(elevator_thread)) {
		printk("ERROR! kthread_run, producer thread\n");
	}
	printk("Module is starting an elevator!\n");
}

int elevator_proc_release(struct inode *sp_inode, struct file *sp_file) {
	kfree(message);
	return 0;
}

void update_requests(int passenger_type, int start_floor, int destination_floor)
{
	bool newRequest;
	struct list_item* pers;
	
	pers = kmalloc(sizeof(struct list_item), KFLAGS);
	pers->person = get_passenger(passenger_type, destination_floor);
	mutex_lock_interruptible(&floor_mutex[start_floor - 1]);
	newRequest = list_empty(&requestList[start_floor - 1]);
	printk("new request on %d to %d of %d, is new %d\n", start_floor, destination_floor, passenger_type,newRequest);
	list_add_tail(&pers->list, &requestList[start_floor - 1]);		
	stats[start_floor - 1].currentWeight += pers->person.weight;
	mutex_unlock(&floor_mutex[start_floor - 1]);
	if (newRequest == true)
	{
		struct list_next* newR;
		newR = kmalloc(sizeof(struct list_next), KFLAGS);
		newR->floor = start_floor;
		mutex_lock_interruptible(&nextstop_lock);
		list_add_tail(&newR->list, &nextStop);
		mutex_unlock(&nextstop_lock);
	}
	
}

static int elevator_init(void) {
	int i;
	fops.open = elevator_proc_open;
	fops.read = elevator_proc_read;
	fops.release = elevator_proc_release;

	begin_elevator =& activate_elevator;
	add_request =& update_requests;
	INIT_LIST_HEAD(&elevator.list);
	INIT_LIST_HEAD(&nextStop);
	elevator.state = STOPPED;
	elevator.currentFloor = 1;
	elevator.nextFloor = 1;
	elevator.currentLoad = 0;
 	mutex_init(&nextstop_lock);
	mutex_init(&elevator_lock);
	for (i = 0; i < MAX_FLOOR; i++)
	{
		INIT_LIST_HEAD(&requestList[i]);
		mutex_init(&floor_mutex[i]);
		stats[i].currentWeight = 0;
		stats[i].serviceCount = 0;	
	}	
	if (!proc_create(ENTRY_NAME, PERMS, NULL, &fops)) {
		printk("ERROR! proc_create\n");
		remove_proc_entry(ENTRY_NAME, NULL);
		return -ENOMEM;
	}
	elevator_syscalls_create();
	return 0;
}

static void elevator_exit(void) {	
	int ret, debug = 0;
	struct list_item* pers;
	struct list_head* temp, *removalList;
	printk("debug %d\n", debug++);
	if (elevator_thread != NULL)
	{
		ret = kthread_stop(elevator_thread);
		if (ret != -EINTR)
			printk("elevator thread has stopped\n");
	}

	printk("debug %d\n", debug++);
	mutex_lock_interruptible(&elevator_lock);
	if (!list_empty(&elevator.list))
	{
		list_for_each_safe(removalList, temp, &elevator.list)
		{
			pers = list_entry(removalList, struct list_item, list);
			list_del(removalList);
			kfree(pers);
		}
	}
	mutex_unlock(&elevator_lock);
	printk("debug %d\n", debug++);
	mutex_lock_interruptible(&nextstop_lock);
	if (!list_empty(&nextStop))
	{
		list_for_each_safe(removalList, temp,  &nextStop)
		{
			pers = list_entry(removalList, struct list_item, list);
			list_del(removalList);
			kfree(pers);
		}
	}
	mutex_unlock(&nextstop_lock);
	printk("debug %d\n", debug++);
	if (state != NULL)
	{
		kfree(state);
	}
	printk("debug %d\n", debug++);
	elevator_syscalls_remove();
	printk("debug %d\n", debug++);
	remove_proc_entry(ENTRY_NAME, NULL);
	printk("debug %d\n", debug++);
}

module_init(elevator_init);
module_exit(elevator_exit);
