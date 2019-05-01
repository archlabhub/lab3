#include "msp430.h"

void lose (char too_slow);
void win (void);

volatile char mode = 10;					// default to easy mode
volatile char flash = 0;					// keeps track of which iteration we are on
volatile int ticks = 0;						// counts the WDT interrupts

int main (void)
{
	WDTCTL = WDTPW + WDTHOLD;				// stop the watchdog timer

	// set up the clocks for the factory preset 1MHz
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	P1DIR = (BIT0 + BIT6);					// enable the two LEDs as outputs
	P1OUT = BIT6;										// flip LED1 on

	// set up the clocks for the LED blink

	// WDTTMSEL = Interval timer mode
	// clock source is SMCLK (1MHz or 1000000Hz)
	// Interval is clock /64 (15625 interrupts per second)
	WDTCTL = WDTPW + WDTTMSEL + WDTCNTCL + WDTIS1 + WDTIS0;

	IE1 |= WDTIE;										// enable WDT interrupt

	// set up the interrupt for the button
	P1IE |= BIT3;
	P1IES |= BIT3;
	P1IFG &= ~BIT3;									// clear the interrupt flag

	_bis_SR_register(LPM1_bits + GIE);	// enter low power mode w/ interrupts
}

void lose (char too_slow)
{
	unsigned int flash_time, x;

	P1OUT &= ~BIT6;									// ensure the the green LED is off
	flash_time = (too_slow) ? 60000 : 6000;

	while (1)												// program end, loop infinitely
	{
		P1OUT ^= BIT0;								// toggle LED1
		for (x = 0; x < flash_time; x++)	// wait
		{
		}
	}
}

void win (void)
{
	P1OUT = BIT6;										// turn on the LED2
	_bis_SR_register(LPM4_bits);		// program end, enter max. power saving mode
}

#pragma vector=WDT_VECTOR
__interrupt void wdt_trigger(void)
{
	// WDT is triggered 15625 times per second, I only want a 1Hz flash for
	// the purpose of choosing a difficulty mode so...
	switch(ticks++)
	{
		case 0:
			if (P1OUT & (BIT0 + BIT6))	// check if we are choosing a difficulty level
			{
				P1OUT ^= (BIT0 + BIT6);		// reverse LED1 and LED2
			}
			else												// we are in a game
			{
				if (++flash <= mode)
				{
					P1OUT ^= (mode == 5) ? BIT0 : BIT6;	// turn on the appropriate LED
				}
				else
				{
					if (flash == 12)
					{
						lose (1);
					}
				}
			}
			break;
		case 1500:
			if ((flash) && (flash <= mode))
			{
				P1OUT ^= (mode == 5) ? BIT0 : BIT6;	// turn off the appropriate LED
			}
			break;
		case 15624:
			ticks = 0;									// reset the counter for the next flash
			break;
	}
}

#pragma vector=PORT1_VECTOR
__interrupt void button_trigger(void)
{
	P1IFG &= ~BIT3;									// clear the interrupt flag

	if (flash)											// check we are in a game
	{
		// a perfect win is when flash=10 and tick=750, 10*15625+750=157000
		// margin of error is ~20% or 157000 + or - 1500
		if ((long)flash * 15625 + ticks > 157000 - 1500)
		{
			if ((long)flash * 15625 + ticks < 157000 + 1500)
			{
				win();										// great timing, win!
			}
			else
			{
				lose(1);									// too slow, lose
			}
		}
		else
		{
			lose(0);										// too fast, lose
		}
	}
	else														// we have just selected a difficulty
	{
		if (P1OUT & BIT0) mode = 5;		// if LED1 was lit switch to hard mode
		P1OUT &= ~(BIT0 + BIT6);			// turn off both the LEDs
		ticks = 1501;									// reset the tick counter
	}
}