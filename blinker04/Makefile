
ARMGNU = arm-none-eabi
#ARMGNU = arm-none-linux-gnueabi

AOPS = --warn --fatal-warnings 
COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding 


all : blinker04.gcc.thumb.hex blinker04.gcc.thumb2.hex

vectors.o : vectors.s
	$(ARMGNU)-as vectors.s -o vectors.o

blinker04.gcc.thumb.o : blinker04.c
	$(ARMGNU)-gcc $(COPS) -mthumb -c blinker04.c -o blinker04.gcc.thumb.o

blinker04.gcc.thumb2.o : blinker04.c
	$(ARMGNU)-gcc $(COPS) -mthumb -mcpu=cortex-m3 -march=armv7-m -c blinker04.c -o blinker04.gcc.thumb2.o

blinker04.gcc.thumb.hex : memmap vectors.o blinker04.gcc.thumb.o
	$(ARMGNU)-ld -o blinker04.gcc.thumb.elf -T memmap vectors.o blinker04.gcc.thumb.o
	$(ARMGNU)-objdump -D blinker04.gcc.thumb.elf > blinker04.gcc.thumb.list
	$(ARMGNU)-objcopy blinker04.gcc.thumb.elf blinker04.gcc.thumb.hex -O ihex

blinker04.gcc.thumb2.hex : memmap vectors.o blinker04.gcc.thumb2.o
	$(ARMGNU)-ld -o blinker04.gcc.thumb2.elf -T memmap vectors.o blinker04.gcc.thumb2.o
	$(ARMGNU)-objdump -D blinker04.gcc.thumb2.elf > blinker04.gcc.thumb2.list
	$(ARMGNU)-objcopy blinker04.gcc.thumb2.elf blinker04.gcc.thumb2.hex -O ihex

clean:
	rm -f *.bin
	rm -f *.hex
	rm -f *.o
	rm -f *.elf
	rm -f *.list

