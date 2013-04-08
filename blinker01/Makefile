
ARMGNU = arm-none-eabi
#ARMGNU = arm-none-linux-gnueabi

AOPS = --warn --fatal-warnings 
COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding 

all : blinker01.gcc.thumb.hex blinker01.gcc.thumb2.hex

vectors.o : vectors.s
	$(ARMGNU)-as vectors.s -o vectors.o

blinker01.gcc.thumb.o : blinker01.c
	$(ARMGNU)-gcc $(COPS) -mthumb -c blinker01.c -o blinker01.gcc.thumb.o

blinker01.gcc.thumb2.o : blinker01.c
	$(ARMGNU)-gcc $(COPS) -mthumb -mcpu=cortex-m3 -march=armv7-m -c blinker01.c -o blinker01.gcc.thumb2.o

blinker01.gcc.thumb.hex : memmap vectors.o blinker01.gcc.thumb.o
	$(ARMGNU)-ld -o blinker01.gcc.thumb.elf -T memmap vectors.o blinker01.gcc.thumb.o
	$(ARMGNU)-objdump -D blinker01.gcc.thumb.elf > blinker01.gcc.thumb.list
	$(ARMGNU)-objcopy blinker01.gcc.thumb.elf blinker01.gcc.thumb.hex -O ihex

blinker01.gcc.thumb2.hex : memmap vectors.o blinker01.gcc.thumb2.o
	$(ARMGNU)-ld -o blinker01.gcc.thumb2.elf -T memmap vectors.o blinker01.gcc.thumb2.o
	$(ARMGNU)-objdump -D blinker01.gcc.thumb2.elf > blinker01.gcc.thumb2.list
	$(ARMGNU)-objcopy blinker01.gcc.thumb2.elf blinker01.gcc.thumb2.hex -O ihex

clean:
	rm -f *.bin
	rm -f *.hex
	rm -f *.o
	rm -f *.elf
	rm -f *.list

