KDIR = /lib/modules/$(shell uname -r)/build
obj-m += mymodule.o
kbuild: 
	make -C $(KDIR) M=$(PWD) modules
	@echo "build success"
clean:
	make -C $(KDIR) M=$(PWD) clean
	@echo "clean success"
	