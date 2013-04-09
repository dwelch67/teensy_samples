
ARMGNU = arm-none-eabi
#ARMGNU = arm-none-linux-gnueabi

AOPS = --warn --fatal-warnings 
COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding 


all : uart02.gcc.thumb.hex uart02.gcc.thumb2.hex

vectors.o : vectors.s
	$(ARMGNU)-as vectors.s -o vectors.o

uart02.gcc.thumb.o : uart02.c
	$(ARMGNU)-gcc $(COPS) -mthumb -c uart02.c -o uart02.gcc.thumb.o

uart02.gcc.thumb2.o : uart02.c
	$(ARMGNU)-gcc $(COPS) -mthumb -mcpu=cortex-m3 -march=armv7-m -c uart02.c -o uart02.gcc.thumb2.o

uart02.gcc.thumb.hex : memmap vectors.o uart02.gcc.thumb.o
	$(ARMGNU)-ld -o uart02.gcc.thumb.elf -T memmap vectors.o uart02.gcc.thumb.o
	$(ARMGNU)-objdump -D uart02.gcc.thumb.elf > uart02.gcc.thumb.list
	$(ARMGNU)-objcopy uart02.gcc.thumb.elf uart02.gcc.thumb.hex -O ihex

uart02.gcc.thumb2.hex : memmap vectors.o uart02.gcc.thumb2.o
	$(ARMGNU)-ld -o uart02.gcc.thumb2.elf -T memmap vectors.o uart02.gcc.thumb2.o
	$(ARMGNU)-objdump -D uart02.gcc.thumb2.elf > uart02.gcc.thumb2.list
	$(ARMGNU)-objcopy uart02.gcc.thumb2.elf uart02.gcc.thumb2.hex -O ihex

clean:
	rm -f *.bin
	rm -f *.hex
	rm -f *.o
	rm -f *.elf
	rm -f *.list

