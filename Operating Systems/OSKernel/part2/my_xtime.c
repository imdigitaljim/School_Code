#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/timekeeping.h>
#include <asm-generic/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Matthew");
MODULE_DESCRIPTION("Simple module providing time since Unix Epoch and last read using proc read");

/*Note: This implementation is heavily based upon code provided by Britton Dennis*/


#define ENTRY_NAME "timed"
#define PERMS 0644
#define PARENT NULL
static struct file_operations fops;

static char *message;
static int read_p;
static int first = 0;
static struct timespec time1, time2;
static char time1Str[30], time2Str[30];

int myXtime_proc_open(struct inode *sp_inode, struct file *sp_file) {
	read_p = 1;
	message = kmalloc(sizeof(char) * 100, __GFP_WAIT | __GFP_IO | __GFP_FS);
	if (message == NULL) {
		printk("ERROR, timed_proc_open");
		return -ENOMEM;
	}
	strcpy(message, "current time: ");
	time1.tv_sec = current_kernel_time().tv_sec;
	time1.tv_nsec = current_kernel_time().tv_nsec;
	sprintf(time1Str, "%lld.%.9ld", (long long)time1.tv_sec, (long)time1.tv_nsec);
	strcat(message, time1Str);
	strcat(message, "\n");
	if(first == 1) {
		strcat(message, "elapsed time: ");
		time2 = timespec_sub(time1, time2);
		sprintf(time2Str, "%lld.%.9ld", (long long)time2.tv_sec, (long)time2.tv_nsec);
		strcat(message, time2Str);
		strcat(message, "\n");
	}
	else 
		++first;
	time2.tv_sec = time1.tv_sec;
	time2.tv_nsec = time1.tv_nsec;
	return 0;
}

ssize_t myXtime_proc_read(struct file *sp_file, char __user *buf, size_t size, loff_t *offset) {
	int len = strlen(message);

	read_p = !read_p;
	if (read_p) {
		return 0;
	}
	copy_to_user(buf, message, len);
	return len;
}

int myXtime_proc_release(struct inode *sp_inode, struct file *sp_file) {
	kfree(message);
	return 0;
}



static int myXtime_init(void) {
	fops.open = myXtime_proc_open;
	fops.read = myXtime_proc_read;
	fops.release = myXtime_proc_release;
	
	if (!proc_create(ENTRY_NAME, PERMS, NULL, &fops)) {
		printk("ERROR! proc_create\n");
		remove_proc_entry(ENTRY_NAME, NULL);
		return -ENOMEM;
	}
	return 0;
}

static void myXtime_exit(void) {
	remove_proc_entry(ENTRY_NAME, NULL);
}

module_init(myXtime_init);
module_exit(myXtime_exit);
