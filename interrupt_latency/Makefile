obj-m	:= latency.o

KERNEL_SRC	:= /lib/modules/$(shell uname -r)/build
PWD	:= $(shell pwd)
EXTRA_CFLAGS := -I/usr/realtime/include 

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD)  modules

clean:
	$(MAKE)  -C $(KERNEL_SRC)  M=$(PWD)  clean
