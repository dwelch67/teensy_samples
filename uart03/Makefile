
ARMGNU = arm-none-eabi
#ARMGNU = arm-none-linux-gnueabi

AOPS = --warn --fatal-warnings 
COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding 


all : uart03.gcc.thumb.hex uart03.gcc.thumb2.hex

vectors.o : vectors.s
	$(ARMGNU)-as vectors.s -o vectors.o

uart03.gcc.thumb.o : uart03.c
	$(ARMGNU)-gcc $(COPS) -mthumb -c uart03.c -o uart03.gcc.thumb.o

uart03.gcc.thumb2.o : uart03.c
	$(ARMGNU)-gcc $(COPS) -mthumb -mcpu=cortex-m3 -march=armv7-m -c uart03.c -o uart03.gcc.thumb2.o

uart03.gcc.thumb.hex : memmap vectors.o uart03.gcc.thumb.o
	$(ARMGNU)-ld -o uart03.gcc.thumb.elf -T memmap vectors.o uart03.gcc.thumb.o
	$(ARMGNU)-objdump -D uart03.gcc.thumb.elf > uart03.gcc.thumb.list
	$(ARMGNU)-objcopy uart03.gcc.thumb.elf uart03.gcc.thumb.hex -O ihex

uart03.gcc.thumb2.hex : memmap vectors.o uart03.gcc.thumb2.o
	$(ARMGNU)-ld -o uart03.gcc.thumb2.elf -T memmap vectors.o uart03.gcc.thumb2.o
	$(ARMGNU)-objdump -D uart03.gcc.thumb2.elf > uart03.gcc.thumb2.list
	$(ARMGNU)-objcopy uart03.gcc.thumb2.elf uart03.gcc.thumb2.hex -O ihex

clean:
	rm -f *.bin
	rm -f *.hex
	rm -f *.o
	rm -f *.elf
	rm -f *.list

