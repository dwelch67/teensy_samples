
ARMGNU = arm-none-eabi
#ARMGNU = arm-none-linux-gnueabi

AOPS = --warn --fatal-warnings 
COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding 


all : uart01.gcc.thumb.hex uart01.gcc.thumb2.hex

vectors.o : vectors.s
	$(ARMGNU)-as vectors.s -o vectors.o

uart01.gcc.thumb.o : uart01.c
	$(ARMGNU)-gcc $(COPS) -mthumb -c uart01.c -o uart01.gcc.thumb.o

uart01.gcc.thumb2.o : uart01.c
	$(ARMGNU)-gcc $(COPS) -mthumb -mcpu=cortex-m3 -march=armv7-m -c uart01.c -o uart01.gcc.thumb2.o

uart01.gcc.thumb.hex : memmap vectors.o uart01.gcc.thumb.o
	$(ARMGNU)-ld -o uart01.gcc.thumb.elf -T memmap vectors.o uart01.gcc.thumb.o
	$(ARMGNU)-objdump -D uart01.gcc.thumb.elf > uart01.gcc.thumb.list
	$(ARMGNU)-objcopy uart01.gcc.thumb.elf uart01.gcc.thumb.hex -O ihex

uart01.gcc.thumb2.hex : memmap vectors.o uart01.gcc.thumb2.o
	$(ARMGNU)-ld -o uart01.gcc.thumb2.elf -T memmap vectors.o uart01.gcc.thumb2.o
	$(ARMGNU)-objdump -D uart01.gcc.thumb2.elf > uart01.gcc.thumb2.list
	$(ARMGNU)-objcopy uart01.gcc.thumb2.elf uart01.gcc.thumb2.hex -O ihex

clean:
	rm -f *.bin
	rm -f *.hex
	rm -f *.o
	rm -f *.elf
	rm -f *.list

