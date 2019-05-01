
all: raceCar.elf

# makfile configuration
COMMON_OBJECTS         =  lcd_backend.o lcd_utils.o sr.o
CPU             = msp430g2553 
CFLAGS          = -mmcu=${CPU} -Os -g 

#switch the compiler (for the internal make rules)
CC              = msp430-gcc
AS              = msp430-as

#additional rules for files

raceCar.elf: raceCar.o lcd_char.o drawGraphics.o ${COMMON_OBJECTS}
	msp430-gcc -mmcu=${CPU} -g -o $@ $^

install_raceCar: raceCar.elf
	mspdebug rf2500 "prog $^"
clean:
	rm -f *.o *.elf



