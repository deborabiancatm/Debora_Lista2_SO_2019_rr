obj-m = todolist.o
KVERSION = 4.18.16-300.fc29.x86_64

all:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean