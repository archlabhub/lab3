all: timeLord.elf

CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as
AR              = msp430-elf-ar

timeLord.elf: timeLord.o
	$(CC) $(CFLAGS) ${LDFLAGS} -o $@ $^ -lLcd -lp2sw -lTimer

clean:
	rm -f *.a *.o *.elf

load: timeLord.elf
	mspdebug rf2500 "prog $^"
