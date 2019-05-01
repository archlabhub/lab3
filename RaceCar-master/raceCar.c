#include <msp430.h>
#include "lcd_char.h"
#include "lcd_utils.h"
#include "drawGraphics.h"
#include <stdlib.h>

#define LEFT -1
#define RIGHT 1
#define MAX_XPOS 50
#define MIN_XPOS 10

#define CENTER_XPOSITION 30
#define LEFT_XPOSITION 10
#define RIGHT_XPOSITION 50

char currentX = 30; // Used for the x position of your car 
char xPos = 0;      // Used for the x position of the enemy car 
char yPos = 0;      // Used for the y position of the enemy car
char start = 0;
char speed = 20;
int score = 0;

void initialize(void);

void mcOsc1MHz(void){         /* set master clock to 1 MHz*/
  BCSCTL1 = CALBC1_1MHZ;    // Set range
  DCOCTL = CALDCO_1MHZ;
  BCSCTL2 &= ~(DIVS_3);    // SMCLK = DCO / 8 = 1MHz
}

interrupt(PORT1_VECTOR) Port_1(void){
  /* We use this for loop to delete the old score */
  int i = 70;                      
  for(i; i < 90; i++)
    lcd_writeChunkAddr(0x00,i,2);

  /* We use this for loop to delete the Game Over message */
  int e = 20;
  for(e; e < 50; e++){
    lcd_writeChunkAddr(0,e,0);
    lcd_writeChunkAddr(0,e,1);
  }
  /* We delete our car, the enemy car, and the explosion graphics */
  // clearCar(currentX,8);
  // clearCar(xPos,yPos-1);
  clearExplosion(xPos, 8);
  clearExplosion(xPos,yPos-1);

  /* We set start = 1 so the game can initialize */
  start = 1;
  initialize();

  // Clear interrupts
  P1IFG &= ~SW1;
  P2IFG &= ~(SW2+SW3+SW4+SW5);
}

main(){
  WDTCTL = WDTPW + WDTHOLD;        // Stop watchdog timer
  lcdinit();                       // init LCD (also: CPU clock to 16MHz)
  lcd_setAddr(0,3); 
  TACTL = TASSEL_2 + MC_1 + ID_3;  // Set timer clock to CPU cloc/8
  CCR0 = 50000;                    // Interrupt every 10 ms
  CCTL0 = CCIE;                    // CCR0 interrupt enabled
  //initialize();
  drawTitleScreen();
  or_sr(0x18);                     // CPU off, GIE on
}

void initialize(void){
  int counter = 0;
  for(counter; counter < 96; counter++){
    lcd_writeChunkAddr(0,counter,0);
    lcd_writeChunkAddr(0,counter,1);
    lcd_writeChunkAddr(0,counter,2);
    lcd_writeChunkAddr(0,counter,3);
    lcd_writeChunkAddr(0,counter,4);
    lcd_writeChunkAddr(0,counter,5);
    lcd_writeChunkAddr(0,counter,6);
    lcd_writeChunkAddr(0,counter,7);
    lcd_writeChunkAddr(0,counter,8);
  }

  lcd_writeString("Score",65,0);
  lcd_writeString("Start",65,7);

  /* This loop draws the division line between the game section and the score 
     section*/
  unsigned int y = 0;
  unsigned char chunk = 0xff;
  while(y < 9){
    lcd_writeChunkAddr(chunk,60,y);
    y += 1;
  }
  currentX = CENTER_XPOSITION;  // The initial position of our car is at the
                                // center
  speed = 20;     // Initial speed is twenty 10ms interrupt calls
  score = 0;
  yPos = 0;
  lcd_writeString("0",73,2); // Initial score
  drawCar(currentX,8); // We draw our car at the current X position and in the
                       // bottom (our car will always be at the bottom)
}

interrupt(TIMER0_A0_VECTOR) Timer_0(void){
  static int count = 1;  // Number of times this interrupt is called
  static int lines = 0;  // Number used to blink the discontinuous lines 

  /* Random number generator for the position of the enemy car
     will be used only when a new car must be created (which is when the 
     y position is 0)*/
  if(yPos == 0){
    int r = rand();
    r = r % 3;
    if(r == 0)
      xPos = LEFT_XPOSITION;
    else if(r == 1)
      xPos = CENTER_XPOSITION;
    else
      xPos = RIGHT_XPOSITION;
  }
 
  /* string where the score will be stored */
  char scoreString[] = "      ";

  if(start){
    /* Here is where we check the speed */
    if(count++ > speed){
      /* Clear previous enemy car and create a new one down of the other */
      clearCar(xPos,yPos-1);
      drawEnemyCar(xPos,yPos);
      
      /* This if else statement alternates the discontinuous lines */
      clearLines(lines);
      if(lines)
	drawLines(--lines);
      else
      	drawLines(++lines);

      /* Here we check if there was a crash. We got to check the next
         position of the enemy car to represent a crash correctly */
      if(((yPos+1) > 6) && (xPos == currentX)){
	/* We delete both cars and replace them with explosion graphics */
	clearCar(xPos,yPos);       
	clearCar(xPos,8);
	drawExplosion(xPos,yPos-1);
	drawExplosion(xPos,8);
	/* Game Over is written in the screen */
	lcd_writeString("Game",20,0);
	lcd_writeString("Over",20,1);
	start = 0;  // We are no longer playing so we set start to false
      }
      
      /* Update the y position of the enemy car */
      yPos++;

      /* if the enemy car is at the bottom, we delete it and we set the
         y position to 0 again, a new rng will decide where it will appear 
         we add one to the score and we draw it to the screen */
      if(yPos > 9){
	clearCar(xPos,9);
	yPos = 0;
	/* add the score int to the string*/
	itoa(++score,scoreString,10);
	/* max score is 9999 */
	if(score > 9998)
	  score = 9999;
	/* every 5 cars we increment the speed */
	if((score % 5) == 0){
	  if(speed != 1)
	    speed /=2;
	}
	/* Write the string to the screen */
	lcd_writeString(scoreString,73,2);
      }
      count = 0;
    }
  }
  /* Do nothing */
  else{}
}

/* Interrupt for direction pad */
interrupt(PORT2_VECTOR) Port_2(void){
  /* If the game is running */
  if(start){
    // check if left switch is pressed
    if(!(P2IN &SW2)){
      updateCar(LEFT);
    }
    // check if right switch is pressed
    else if(!(P2IN & SW5)){
      updateCar(RIGHT);
    }
  }
  // clear interrup from right hand Switch
  //P1IFG &= ~SW1;
  // clear interrupts from direction switches
  P2IFG &= ~(SW2+SW3+SW4+SW5);
}

/* changes user car to the correct position*/
void updateCar(int direction)
{
  if(direction == LEFT)
    {
      clearCar(currentX,8);      // delete current car
      currentX = currentX - 20;  // set current position to the left of current
      /* If we are on the far left, we restore the position */
      if(currentX < MIN_XPOS)
	{
	  currentX = currentX + 20;
	}
      drawCar(currentX,8);       // draw new car
    }
  else
    {
      clearCar(currentX,8);      
      currentX = currentX + 20;
      /* If we are on the far right, we restore position */
      if(currentX > MAX_XPOS)
	{
	  currentX = currentX - 20;
	}
      drawCar(currentX,8);
    }
}
