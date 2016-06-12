# obj-m := romfs.o
# romfs-y := super.o storage.o
# KDIR := /lib/modules/$(shell uname -r)/build
# EXTRA_FLAGS := -I(PWD)
# PWD := $(shell pwd)

obj-m:= romfs.o
romfs-y := super.o storage.o
KDIR:= /lib/modules/$(shell uname -r)/build
PWD:= $(shell pwd)
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean