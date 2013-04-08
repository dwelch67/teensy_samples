
ARMGNU = arm-none-eabi
#ARMGNU = arm-none-linux-gnueabi

AOPS = --warn --fatal-warnings 
COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding 

all : blinker02.gcc.thumb.hex blinker02.gcc.thumb2.hex

vectors.o : vectors.s
	$(ARMGNU)-as vectors.s -o vectors.o

blinker02.gcc.thumb.o : blinker02.c
	$(ARMGNU)-gcc $(COPS) -mthumb -c blinker02.c -o blinker02.gcc.thumb.o

blinker02.gcc.thumb2.o : blinker02.c
	$(ARMGNU)-gcc $(COPS) -mthumb -mcpu=cortex-m3 -march=armv7-m -c blinker02.c -o blinker02.gcc.thumb2.o

blinker02.gcc.thumb.hex : memmap vectors.o blinker02.gcc.thumb.o
	$(ARMGNU)-ld -o blinker02.gcc.thumb.elf -T memmap vectors.o blinker02.gcc.thumb.o
	$(ARMGNU)-objdump -D blinker02.gcc.thumb.elf > blinker02.gcc.thumb.list
	$(ARMGNU)-objcopy blinker02.gcc.thumb.elf blinker02.gcc.thumb.hex -O ihex

blinker02.gcc.thumb2.hex : memmap vectors.o blinker02.gcc.thumb2.o
	$(ARMGNU)-ld -o blinker02.gcc.thumb2.elf -T memmap vectors.o blinker02.gcc.thumb2.o
	$(ARMGNU)-objdump -D blinker02.gcc.thumb2.elf > blinker02.gcc.thumb2.list
	$(ARMGNU)-objcopy blinker02.gcc.thumb2.elf blinker02.gcc.thumb2.hex -O ihex

clean:
	rm -f *.bin
	rm -f *.hex
	rm -f *.o
	rm -f *.elf
	rm -f *.list

