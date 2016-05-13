obj-m:= mtest.o
KDIR:= /lib/modules/$(shell uname -r)/build
PWD:= $(shell pwd)
all:
	make -C $(KDIR) M=$(PWD) modules
	g++ test.c -o test
clean:
	make -C $(KDIR) M=$(PWD) clean
	rm test
