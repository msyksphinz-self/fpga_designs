CC = arm-linux-gnueabihf-gcc
CFLAGS = -g

all : led_blink

led_blink : led_blink.o
	$(CC) $(CFLAGS) $^ -o $@

clean :
	rm -rfv *.o
	rm -rfv led_blink

.PHONY : clean
