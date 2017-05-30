BUILD_DIR := $(shell pwd)
obj-m := myled.o

all:
	make -C ../../linux-xlnx/ M=$(BUILD_DIR) modules

clean:
	make -C ../../linux-xlnx M=$(BUILD_DIR) clean
