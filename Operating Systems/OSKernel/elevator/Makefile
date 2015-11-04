MODULE_NAME = elevator
# Point to module code
PWD := $(shell pwd)

#kernel libraries
#KDIR := /lib/modules/$(shell uname -r)/build
KDIR := /lib/modules/4.2.0/build
#compile header flags
ccflags-y += -I$(src)/include 


#built-in code do not modify!
obj-y := src/sys_start_elevator.o
obj-y += src/sys_issue_request.o
obj-y += src/sys_stop_elevator.o
#################################

$(MODULE_NAME)-objs += src/syscalls.o
$(MODULE_NAME)-objs += src/module.o
#add source files here
#
#module object
obj-m := $(MODULE_NAME).o

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
