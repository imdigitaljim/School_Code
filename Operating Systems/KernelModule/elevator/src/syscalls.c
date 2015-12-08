#include <syscalls.h>
#include <linux/printk.h>
/*#include <linux/init.h>
#include <linux/module.h>*/
#define NUM_TYPES 4
#define MIN_FLOOR 1
#define MAX_FLOOR 10

int isActive = 0;
int isRunning = 0;

void (*begin_elevator)(void) = NULL;
void (*add_request)(int,int,int) = NULL;



extern long (*STUB_start_elevator)(void);
long start_elevator(void) {
	if (isActive == 0)
	{
		isActive = 1;
		begin_elevator();
		return 0;
	}
	return 1;
}

extern long (*STUB_issue_request)(int,int,int);
long issue_request(int passenger_type, int start_floor, int destination_floor) {
	if (isActive != 0 || passenger_type < 0 || passenger_type > NUM_TYPES - 1 || start_floor < MIN_FLOOR || destination_floor > MAX_FLOOR)
	{
		isRunning = 1;
		printk("New request: %d, %d => %d\n", passenger_type, start_floor, destination_floor);
		add_request(passenger_type, start_floor, destination_floor);
		return 0;
	}
	return 1;
}

extern long (*STUB_stop_elevator)(void);
long stop_elevator(void) {
	printk("Stopping elevator\n");
	isActive = 0;	
	return isRunning;
}

void elevator_syscalls_create(void) {
	STUB_start_elevator =& (start_elevator);
	STUB_issue_request =& (issue_request);
	STUB_stop_elevator =& (stop_elevator);
}

void elevator_syscalls_remove(void) {
	STUB_start_elevator = NULL;
	STUB_issue_request = NULL;
	STUB_stop_elevator = NULL;
}
