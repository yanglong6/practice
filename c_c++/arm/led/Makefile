CROSS = arm-none-linux-gnueabi-
CC=$(CROSS)gcc
LD=$(CROSS)ld
OBJCOPY=$(CROSS)objcopy
    
all: led.s
	$(CC) -g -c -o led.o led.s  
	$(LD) led.o -Ttext 0x43e00000 -o led.elf
	$(OBJCOPY)  -O binary -S led.elf led.bin
	$(CROSS)objdump -D led.elf > led.dis
	 
clean:
	rm -f *.o *.elf *.bin *.dis
