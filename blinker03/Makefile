
ARMGNU = arm-none-eabi
#ARMGNU = arm-none-linux-gnueabi

AOPS = --warn --fatal-warnings 
COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding 


all : blinker03.gcc.thumb.hex blinker03.gcc.thumb2.hex

vectors.o : vectors.s
	$(ARMGNU)-as vectors.s -o vectors.o

blinker03.gcc.thumb.o : blinker03.c
	$(ARMGNU)-gcc $(COPS) -mthumb -c blinker03.c -o blinker03.gcc.thumb.o

blinker03.gcc.thumb2.o : blinker03.c
	$(ARMGNU)-gcc $(COPS) -mthumb -mcpu=cortex-m3 -march=armv7-m -c blinker03.c -o blinker03.gcc.thumb2.o

blinker03.gcc.thumb.hex : memmap vectors.o blinker03.gcc.thumb.o
	$(ARMGNU)-ld -o blinker03.gcc.thumb.elf -T memmap vectors.o blinker03.gcc.thumb.o
	$(ARMGNU)-objdump -D blinker03.gcc.thumb.elf > blinker03.gcc.thumb.list
	$(ARMGNU)-objcopy blinker03.gcc.thumb.elf blinker03.gcc.thumb.hex -O ihex

blinker03.gcc.thumb2.hex : memmap vectors.o blinker03.gcc.thumb2.o
	$(ARMGNU)-ld -o blinker03.gcc.thumb2.elf -T memmap vectors.o blinker03.gcc.thumb2.o
	$(ARMGNU)-objdump -D blinker03.gcc.thumb2.elf > blinker03.gcc.thumb2.list
	$(ARMGNU)-objcopy blinker03.gcc.thumb2.elf blinker03.gcc.thumb2.hex -O ihex

clean:
	rm -f *.bin
	rm -f *.hex
	rm -f *.o
	rm -f *.elf
	rm -f *.list

