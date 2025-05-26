MODULE=hello
T_ADDR=192.168.64.9
T_USER=gschons
T_PATH=/home/$(T_USER)/kernel-module

obj-m += hello.o

build:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

init:
	sudo insmod $(MODULE).ko

remove:
	sudo rmmod $(MODULE)

sync:
	rsync -avz --exclude='.git' --exclude='README.md' --progress ./ $(T_USER)@$(T_ADDR):$(T_PATH)

.PHONY: deploy clean init remove sync
