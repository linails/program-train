ifneq ($(KERNELRELEASE),)

obj-m := kernel-module-hw.o
#kernel-module-hw-objs := axx.o bxx.o

else
	
# 内核源代码路径
KDIR := /mini6410/linux/linux-2.6.38
all:
	#make -C $(KDIR) M=$(PWD) modules ARCH=arm CROSS_COMPILE=arm-linux-
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers  modul*

endif
