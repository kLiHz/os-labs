obj-m += showPCB.o

PWD := $(CURDIR)
BUILDDIR := /lib/modules/$(shell uname -r)/build

all:
	make -C $(BUILDDIR) M=$(PWD) modules 

clean: 
	make -C $(BUILDDIR) M=$(PWD) clean
