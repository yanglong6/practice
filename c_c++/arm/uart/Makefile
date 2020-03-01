all:
	arm-none-linux-gnueabi-gcc -fno-builtin -nostdinc -c -o start.o start.S
	arm-none-linux-gnueabi-gcc -fno-builtin -nostdinc -c -o main.o main.c
	arm-none-linux-gnueabi-ld start.o main.o -Tmap.lds -o uart.elf
	arm-none-linux-gnueabi-objcopy -O binary  uart.elf uart.bin
	arm-none-linux-gnueabi-objdump -D uart.elf > uart.dis
clean:
	rm -rf *.o uart.*

