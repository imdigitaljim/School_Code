#ifndef __ELEVATOR_SYSCALLS_H
#define __ELEVATOR_SYSCALLS_H
#include <linux/list.h>

/* References for module to call; Passes creation/removal to syscall.c*/
void elevator_syscalls_create(void);
void elevator_syscalls_remove(void);

extern int isActive;
extern int isRunning;

/*lock me when editing*/
extern void (*begin_elevator)(void);
extern void (*add_request)(int,int,int);
#endif /*__ELEVATOR_SYSCALLS_H*/


