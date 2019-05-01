#include "lcd_utils.h"
#include "drawGraphics.h"

 //this method draws the user's car
void drawCar(char xPos, char yPos)
{
  char x = xPos - 6; //Used to draw the car starting from the "spawning" point of the car
  int i;
  
  //This loop draws the left wheels of the car
  for(i = 0; i < 3; i++){
    lcd_writeChunkAddr(0x3,x,yPos);
    lcd_writeChunkAddr(0xcf,x,yPos-1);
    x++;
  }
  
  //these statements draw the "outline" of the chassis of the car
  lcd_writeChunkAddr(0xf,x,yPos);
  lcd_writeChunkAddr(0xff,x,yPos-1);
  lcd_writeChunkAddr(0xc0,x,yPos-2);
  x++;

  for(i = 0; i < 4; i++){
    lcd_writeChunkAddr(0x8, x, yPos);
    lcd_writeChunkAddr(0x0,x,yPos-1);
    lcd_writeChunkAddr(0x40,x,yPos-2);
    x++;
  }

  lcd_writeChunkAddr(0xf,x,yPos);
  lcd_writeChunkAddr(0xff,x,yPos-1);
  lcd_writeChunkAddr(0xc0,x,yPos-2);
  x++;
  
  //this loop draws the right wheels of the car
  for(i = 0; i < 3; i++){
    lcd_writeChunkAddr(0x3,x,yPos);
    lcd_writeChunkAddr(0xcf,x,yPos-1);
    x++;
  }
}

/*this method draws different cars to make it easier for 
  the player to tell them apart from the main car*/
void drawEnemyCar(char xPos ,char yPos){
  char x = xPos - 6;
  int i;
  //This loop draws the left wheels of the car
  for(i = 0; i < 3; i++){
    lcd_writeChunkAddr(0x3,x,yPos);
    lcd_writeChunkAddr(0xcf,x,yPos-1);
    x++;
  }
  
  //These statements draw the chassis of the car:
  lcd_writeChunkAddr(0xf,x,yPos);
  lcd_writeChunkAddr(0xff,x,yPos-1);
  lcd_writeChunkAddr(0xc0,x,yPos-2);
  x++;

  /*these statements draw the dotted pattern given to enemy cars to
    make them appear gray*/
  for(i = 0; i < 2; i++){
    lcd_writeChunkAddr(0xA, x, yPos);
    lcd_writeChunkAddr(0xAA,x,yPos-1);
    lcd_writeChunkAddr(0xC0,x,yPos-2);
    x+=2;
  }

  x= x-3;

  for(i = 0; i < 2; i++){
    lcd_writeChunkAddr(0xD,x,yPos);
    lcd_writeChunkAddr(0x55,x,yPos-1);
    lcd_writeChunkAddr(0x40,x,yPos-2);
    x+=2;    
  }
  x--;

  lcd_writeChunkAddr(0xf,x,yPos);
  lcd_writeChunkAddr(0xff,x,yPos-1);
  lcd_writeChunkAddr(0xc0,x,yPos-2);
  x++;
  
  //This for loop draws the right wheels
  for(i = 0; i < 3; i++){
    lcd_writeChunkAddr(0x3,x,yPos);
    lcd_writeChunkAddr(0xcf,x,yPos-1);
    x++;
  }
}

//Method used to erase the space previously occupied by cars
void clearCar(char xPos,char yPos)
{
  char x = xPos-6;
  int i;
  for(i = 0; i < 12; i++){
    lcd_writeChunkAddr(0, x, yPos);
    lcd_writeChunkAddr(0,x,yPos-1);
    lcd_writeChunkAddr(0,x,yPos-2);
    x++;
  }
}

/*Method used to draw the discontinuous lines at both edges of the street.
  it alternates between two different patterns to simulate movement*/
void drawLines(char y){
  for(y; y < 9; y+=2){
    lcd_writeChunkAddr(0xff,0,y);
    lcd_writeChunkAddr(0xff,1,y);
    lcd_writeChunkAddr(0xff,57,y);
    lcd_writeChunkAddr(0xff,58,y);
  }
}

/*Method used to erase the previous pattern of lines to make way for
  the new pattern of lines*/
void clearLines(char y){
  for(y; y < 9; y+=2){
    lcd_writeChunkAddr(0x00,0,y);
    lcd_writeChunkAddr(0x00,1,y);
    lcd_writeChunkAddr(0x00,57,y);
    lcd_writeChunkAddr(0x00,58,y);
  }
}

/*Method used to draw an "explosion" graphic. This graphic
looks like an asterisk without the middle part*/
void drawExplosion(char xPos,char yPos){
  char x = xPos - 4;
  
  //these statements draw the left half of the graphic
  lcd_writeChunkAddr(0x80,x++,yPos-1);

  lcd_writeChunkAddr(0x4,x,yPos);
  lcd_writeChunkAddr(0x90,x++,yPos-1);

  lcd_writeChunkAddr(0x2,x,yPos);
  lcd_writeChunkAddr(0xA0,x++,yPos-1);

  x++;

  //thses statements draw the exact middle point of the graphic
  lcd_writeChunkAddr(0xE,x,yPos);
  lcd_writeChunkAddr(0x38,x++,yPos-1);

  x++;

  /*these statements are a mirrored pattern of the left-half chunk of statements 
    they draw the right half of the graphic.*/
  lcd_writeChunkAddr(0x2,x,yPos);
  lcd_writeChunkAddr(0xA0,x++,yPos-1);

  lcd_writeChunkAddr(0x4,x,yPos);
  lcd_writeChunkAddr(0x90,x++,yPos-1);

  lcd_writeChunkAddr(0x80,x,yPos-1);

}

//this method is used to clear the pixels where an explosion graphic was drawn
void clearExplosion(char xPos, char yPos){
  char x = xPos - 4;
  char limit = x+9;
  char i = 0;
  for(i; i < 9;i++){
    lcd_writeChunkAddr(0,x,yPos);
    lcd_writeChunkAddr(0,x,yPos-1);
    x++;
  }
}

void drawTitleScreen(){
  lcd_writeChunkAddr(0x7,0,8);
  lcd_writeChunkAddr(0xff,0,7);

  lcd_writeChunkAddr(0xe,1,8);
  lcd_writeChunkAddr(0x3f,1,7);
  lcd_writeChunkAddr(0xf0,1,6);

  lcd_writeChunkAddr(0xf,2,8);
  lcd_writeChunkAddr(0x83,2,7);
  lcd_writeChunkAddr(0xff,2,6);

  lcd_writeChunkAddr(0x7,3,8);
  lcd_writeChunkAddr(0xf8,3,7);
  lcd_writeChunkAddr(0x7f,3,6);
  lcd_writeChunkAddr(0xe0,3,5);

  lcd_writeChunkAddr(0x1,4,8);
  lcd_writeChunkAddr(0xff,4,7);
  lcd_writeChunkAddr(0x0f,4,6);
  lcd_writeChunkAddr(0xfc,4,5);

  lcd_writeChunkAddr(0x7f,5,7);
  lcd_writeChunkAddr(0xe0,5,6);
  lcd_writeChunkAddr(0xff,5,5);
  lcd_writeChunkAddr(0xc0,5,4);

  lcd_writeChunkAddr(0x07,6,7);
  lcd_writeChunkAddr(0xfe,6,6);
  lcd_writeChunkAddr(0x1f,6,5);
  lcd_writeChunkAddr(0xf8,6,4);

  lcd_writeChunkAddr(0xff,7,6);
  lcd_writeChunkAddr(0xc3,7,5);
  lcd_writeChunkAddr(0xff,7,4);
  lcd_writeChunkAddr(0x80,7,3);

  lcd_writeChunkAddr(0x1f,8,6);
  lcd_writeChunkAddr(0xf8,8,5);
  lcd_writeChunkAddr(0x3f,8,4);
  lcd_writeChunkAddr(0xf0,8,3);

  lcd_writeChunkAddr(0x01,9,6);
  lcd_writeChunkAddr(0xff,9,5);
  lcd_writeChunkAddr(0x87,9,4);
  lcd_writeChunkAddr(0xfe,9,3);

  lcd_writeChunkAddr(0x3f,10,5);
  lcd_writeChunkAddr(0xf0,10,4);
  lcd_writeChunkAddr(0x7f,10,3);
  lcd_writeChunkAddr(0xe0,10,2);

  lcd_writeChunkAddr(0x0f,11,5);
  lcd_writeChunkAddr(0xff,11,4);
  lcd_writeChunkAddr(0x0f,11,3);
  lcd_writeChunkAddr(0xfc,11,2);

  lcd_writeChunkAddr(0x07,12,5);
  lcd_writeChunkAddr(0xff,12,4);
  lcd_writeChunkAddr(0xe1,12,3);
  lcd_writeChunkAddr(0xff,12,2);
  lcd_writeChunkAddr(0x80,12,1);

  lcd_writeChunkAddr(0x07,13,5);
  lcd_writeChunkAddr(0xff,13,4);
  lcd_writeChunkAddr(0xdc,13,3);
  lcd_writeChunkAddr(0x1f,13,2);
  lcd_writeChunkAddr(0xf8,13,1);

  lcd_writeChunkAddr(0x07,14,5);
  lcd_writeChunkAddr(0xff,14,4);
  lcd_writeChunkAddr(0xc3,14,3);
  lcd_writeChunkAddr(0xc3,14,2);
  lcd_writeChunkAddr(0xff,14,1);

  lcd_writeChunkAddr(0x07,15,5);
  lcd_writeChunkAddr(0xff,15,4);
  lcd_writeChunkAddr(0xc0,15,3);
  lcd_writeChunkAddr(0xf8,15,2);
  lcd_writeChunkAddr(0x7f,15,1);
  lcd_writeChunkAddr(0xf0,15,0);

  lcd_writeChunkAddr(0x07,16,5);
  lcd_writeChunkAddr(0xff,16,4);
  lcd_writeChunkAddr(0xc0,16,3);
  lcd_writeChunkAddr(0x7f,16,2);
  lcd_writeChunkAddr(0x07,16,1);
  lcd_writeChunkAddr(0xfe,16,0);

  lcd_writeChunkAddr(0x07,17,5);
  lcd_writeChunkAddr(0xff,17,4);
  lcd_writeChunkAddr(0xc0,17,3);
  lcd_writeChunkAddr(0x7f,17,2);
  lcd_writeChunkAddr(0xf0,17,1);
  lcd_writeChunkAddr(0xff,17,0);

  lcd_writeChunkAddr(0x0f,18,5);
  lcd_writeChunkAddr(0xff,18,4);
  lcd_writeChunkAddr(0xc0,18,3);
  lcd_writeChunkAddr(0x7f,18,2);
  lcd_writeChunkAddr(0xfe,18,1);
  lcd_writeChunkAddr(0x0f,18,0);

  lcd_writeChunkAddr(0x1f,19,6);
  lcd_writeChunkAddr(0xff,19,5);
  lcd_writeChunkAddr(0xff,19,4);
  lcd_writeChunkAddr(0xe0,19,3);
  lcd_writeChunkAddr(0x7f,19,2);
  lcd_writeChunkAddr(0xf1,19,1);
  lcd_writeChunkAddr(0xe1,19,0);

  lcd_writeChunkAddr(0x1f,20,6);
  lcd_writeChunkAddr(0xff,20,5);
  lcd_writeChunkAddr(0xff,20,4);
  lcd_writeChunkAddr(0xe0,20,3);
  lcd_writeChunkAddr(0x7f,20,2);
  lcd_writeChunkAddr(0xf0,20,1);
  lcd_writeChunkAddr(0x1f,20,0);

  lcd_writeChunkAddr(0x1e,21,6);
  lcd_writeChunkAddr(0x7f,21,4);
  lcd_writeChunkAddr(0xe0,21,3);
  lcd_writeChunkAddr(0x7f,21,2);
  lcd_writeChunkAddr(0xf0,21,1);
  lcd_writeChunkAddr(0x1f,21,0);

  lcd_writeChunkAddr(0x1e,22,6);
  lcd_writeChunkAddr(0x63,22,4);
  lcd_writeChunkAddr(0xe0,22,3);
  lcd_writeChunkAddr(0x3f,22,2);
  lcd_writeChunkAddr(0xf0,22,1);
  lcd_writeChunkAddr(0x0e,22,0);

  lcd_writeChunkAddr(0x1e,23,6);
  lcd_writeChunkAddr(0x60,23,4);
  lcd_writeChunkAddr(0x70,23,3);
  lcd_writeChunkAddr(0x3f,23,2);
  lcd_writeChunkAddr(0xf0,23,1);
  lcd_writeChunkAddr(0x0e,23,0);

  lcd_writeChunkAddr(0x1e,24,6);
  lcd_writeChunkAddr(0x60,24,4);
  lcd_writeChunkAddr(0x7c,24,3);
  lcd_writeChunkAddr(0x3f,24,2);
  lcd_writeChunkAddr(0xf0,24,1);
  lcd_writeChunkAddr(0x0e,24,0);

  lcd_writeChunkAddr(0x1e,25,6);
  lcd_writeChunkAddr(0x7e,25,5);
  lcd_writeChunkAddr(0x60,25,4);
  lcd_writeChunkAddr(0x7f,25,3);
  lcd_writeChunkAddr(0xbf,25,2);
  lcd_writeChunkAddr(0xf8,25,1);
  lcd_writeChunkAddr(0x0e,25,0);

  lcd_writeChunkAddr(0x1e,26,6);
  lcd_writeChunkAddr(0x7e,26,5);
  lcd_writeChunkAddr(0x60,26,4);
  lcd_writeChunkAddr(0x7f,26,3);
  lcd_writeChunkAddr(0xff,26,2);
  lcd_writeChunkAddr(0xf8,26,1);
  lcd_writeChunkAddr(0x0e,26,0);

  lcd_writeChunkAddr(0x1e,27,6);
  lcd_writeChunkAddr(0x7e,27,5);
  lcd_writeChunkAddr(0x60,27,4);
  lcd_writeChunkAddr(0xff,27,3);
  lcd_writeChunkAddr(0xc7,27,2);
  lcd_writeChunkAddr(0xf8,27,1);
  lcd_writeChunkAddr(0x0e,27,0);

  lcd_writeChunkAddr(0x1e,28,6);
  lcd_writeChunkAddr(0x7e,28,5);
  lcd_writeChunkAddr(0x60,28,4);
  lcd_writeChunkAddr(0xff,28,3);
  lcd_writeChunkAddr(0xc0,28,2);
  lcd_writeChunkAddr(0xf8,28,1);
  lcd_writeChunkAddr(0x07,28,0);

  lcd_writeChunkAddr(0x1e,29,6);
  lcd_writeChunkAddr(0x7e,29,5);
  lcd_writeChunkAddr(0x60,29,4);
  lcd_writeChunkAddr(0xff,29,3);
  lcd_writeChunkAddr(0xc0,29,2);
  lcd_writeChunkAddr(0x1c,29,1);
  lcd_writeChunkAddr(0x07,29,0);

  lcd_writeChunkAddr(0x1e,30,6);
  lcd_writeChunkAddr(0x7e,30,5);
  lcd_writeChunkAddr(0x61,30,4);
  lcd_writeChunkAddr(0xff,30,3);
  lcd_writeChunkAddr(0x80,30,2);
  lcd_writeChunkAddr(0x1f,30,1);
  lcd_writeChunkAddr(0x87,30,0);

  lcd_writeChunkAddr(0x1f,31,6);
  lcd_writeChunkAddr(0xff,31,5);
  lcd_writeChunkAddr(0xe1,31,4);
  lcd_writeChunkAddr(0xff,31,3);
  lcd_writeChunkAddr(0x80,31,2);
  lcd_writeChunkAddr(0x1f,31,1);
  lcd_writeChunkAddr(0xf7,31,0);

  lcd_writeChunkAddr(0x1f,32,6);
  lcd_writeChunkAddr(0xff,32,5);
  lcd_writeChunkAddr(0xfb,32,4);
  lcd_writeChunkAddr(0xff,32,3);
  lcd_writeChunkAddr(0x80,32,2);
  lcd_writeChunkAddr(0x1f,32,1);
  lcd_writeChunkAddr(0xff,32,0);

  lcd_writeChunkAddr(0xff,33,6);
  lcd_writeChunkAddr(0xff,33,5);
  lcd_writeChunkAddr(0xff,33,4);
  lcd_writeChunkAddr(0xff,33,3);
  lcd_writeChunkAddr(0x3f,33,1);
  lcd_writeChunkAddr(0xfe,33,0);

  lcd_writeChunkAddr(0xff,34,6);
  lcd_writeChunkAddr(0xff,34,5);
  lcd_writeChunkAddr(0xfc,34,4);
  lcd_writeChunkAddr(0xff,34,3);
  lcd_writeChunkAddr(0x3f,34,1);
  lcd_writeChunkAddr(0xfe,34,0);

  lcd_writeChunkAddr(0xf0,35,6);
  lcd_writeChunkAddr(0x03,35,5);
  lcd_writeChunkAddr(0xf8,35,4);
  lcd_writeChunkAddr(0x3e,35,3);
  lcd_writeChunkAddr(0x3f,35,1);
  lcd_writeChunkAddr(0xfe,35,0);

  lcd_writeChunkAddr(0xf0,36,6);
  lcd_writeChunkAddr(0x03,36,5);
  lcd_writeChunkAddr(0xf0,36,4);
  lcd_writeChunkAddr(0x07,36,3);
  lcd_writeChunkAddr(0x80,36,2);
  lcd_writeChunkAddr(0x7f,36,1);
  lcd_writeChunkAddr(0xfe,36,0);

  lcd_writeChunkAddr(0xf0,37,6);
  lcd_writeChunkAddr(0x03,37,5);
  lcd_writeChunkAddr(0xf0,37,4);
  lcd_writeChunkAddr(0x07,37,3);
  lcd_writeChunkAddr(0xf3,37,2);
  lcd_writeChunkAddr(0xff,37,1);
  lcd_writeChunkAddr(0xfc,37,0);

  lcd_writeChunkAddr(0xf0,38,6);
  lcd_writeChunkAddr(0x03,38,5);
  lcd_writeChunkAddr(0x70,38,4);
  lcd_writeChunkAddr(0x0f,38,3);
  lcd_writeChunkAddr(0xff,38,2);
  lcd_writeChunkAddr(0xff,38,1);
  lcd_writeChunkAddr(0xfe,38,0);

  lcd_writeChunkAddr(0x3f,39,6);
  lcd_writeChunkAddr(0x33,39,5);
  lcd_writeChunkAddr(0xc0,39,4);
  lcd_writeChunkAddr(0x1f,39,3);
  lcd_writeChunkAddr(0xff,39,2);
  lcd_writeChunkAddr(0xc0,39,1);
  lcd_writeChunkAddr(0x0c,39,0);


  lcd_writeChunkAddr(0x3f,40,6);
  lcd_writeChunkAddr(0x33,40,5);
  lcd_writeChunkAddr(0xc0,40,4);
  lcd_writeChunkAddr(0x1f,40,3);
  lcd_writeChunkAddr(0xff,40,2);
  lcd_writeChunkAddr(0xc0,40,1);
  lcd_writeChunkAddr(0x0c,40,0);

  lcd_writeChunkAddr(0xf0,41,6);
  lcd_writeChunkAddr(0x03,41,5);
  lcd_writeChunkAddr(0xf0,41,4);
  lcd_writeChunkAddr(0x3f,41,3);
  lcd_writeChunkAddr(0xff,41,2);
  lcd_writeChunkAddr(0xc0,41,1);
  lcd_writeChunkAddr(0x0c,41,0);

  lcd_writeChunkAddr(0xf0,42,6);
  lcd_writeChunkAddr(0x03,42,5);
  lcd_writeChunkAddr(0xfe,42,4);
  lcd_writeChunkAddr(0x7f,42,3);
  lcd_writeChunkAddr(0xff,42,2);
  lcd_writeChunkAddr(0xc0,42,1);
  lcd_writeChunkAddr(0x0c,42,0);

  lcd_writeChunkAddr(0xf0,43,6);
  lcd_writeChunkAddr(0x03,43,5);
  lcd_writeChunkAddr(0xff,43,4);
  lcd_writeChunkAddr(0xff,43,3);
  lcd_writeChunkAddr(0xfc,43,2);
  lcd_writeChunkAddr(0xfc,43,1);
  lcd_writeChunkAddr(0xcc,43,0);

  lcd_writeChunkAddr(0xf0,44,6);
  lcd_writeChunkAddr(0x03,44,5);
  lcd_writeChunkAddr(0xff,44,4);
  lcd_writeChunkAddr(0x1f,44,3);
  lcd_writeChunkAddr(0xf8,44,2);
  lcd_writeChunkAddr(0xfc,44,1);
  lcd_writeChunkAddr(0xcc,44,0);

  lcd_writeChunkAddr(0xff,45,6);
  lcd_writeChunkAddr(0xff,45,5);
  lcd_writeChunkAddr(0xfe,45,4);
  lcd_writeChunkAddr(0x03,45,3);
  lcd_writeChunkAddr(0xf3,45,2);
  lcd_writeChunkAddr(0xc0,45,1);
  lcd_writeChunkAddr(0x0c,45,0);

  lcd_writeChunkAddr(0x01,46,7);
  lcd_writeChunkAddr(0xff,46,6);
  lcd_writeChunkAddr(0xff,46,5);
  lcd_writeChunkAddr(0xfc,46,4);
  lcd_writeChunkAddr(0x73,46,2);
  lcd_writeChunkAddr(0xc0,46,1);
  lcd_writeChunkAddr(0x0c,46,0);

  lcd_writeChunkAddr(0x0f,47,7);
  lcd_writeChunkAddr(0xff,47,6);
  lcd_writeChunkAddr(0xff,47,5);
  lcd_writeChunkAddr(0xfc,47,4);
  lcd_writeChunkAddr(0x7f,47,2);
  lcd_writeChunkAddr(0xc3,47,1);
  lcd_writeChunkAddr(0x0c,47,0);

  lcd_writeChunkAddr(0x0f,48,7);
  lcd_writeChunkAddr(0xff,48,6);
  lcd_writeChunkAddr(0xff,48,5);
  lcd_writeChunkAddr(0xf8,48,4);
  lcd_writeChunkAddr(0xff,48,2);
  lcd_writeChunkAddr(0xc3,48,1);
  lcd_writeChunkAddr(0x0c,48,0);

  lcd_writeChunkAddr(0x0f,49,7);
  lcd_writeChunkAddr(0x3f,49,5);
  lcd_writeChunkAddr(0xf0,49,4);
  lcd_writeChunkAddr(0x01,49,3);
  lcd_writeChunkAddr(0xff,49,2);
  lcd_writeChunkAddr(0xff,49,1);
  lcd_writeChunkAddr(0xfc,49,0);

  lcd_writeChunkAddr(0x1f,50,7);
  lcd_writeChunkAddr(0x33,50,5);
  lcd_writeChunkAddr(0x70,50,4);
  lcd_writeChunkAddr(0x01,50,3);
  lcd_writeChunkAddr(0xff,50,2);
  lcd_writeChunkAddr(0xff,50,1);
  lcd_writeChunkAddr(0xfc,50,0);

  lcd_writeChunkAddr(0x1f,51,7);
  lcd_writeChunkAddr(0x30,51,5);
  lcd_writeChunkAddr(0x78,51,4);
  lcd_writeChunkAddr(0x03,51,3);
  lcd_writeChunkAddr(0xff,51,2);
  lcd_writeChunkAddr(0xff,51,1);
  lcd_writeChunkAddr(0xf0,51,0);

  lcd_writeChunkAddr(0x3f,52,7);
  lcd_writeChunkAddr(0x30,52,5);
  lcd_writeChunkAddr(0xff,52,4);
  lcd_writeChunkAddr(0x07,52,3);
  lcd_writeChunkAddr(0xff,52,2);
  lcd_writeChunkAddr(0xff,52,1);
  lcd_writeChunkAddr(0xf0,52,0);

  lcd_writeChunkAddr(0x7f,53,7);
  lcd_writeChunkAddr(0xf3,53,6);
  lcd_writeChunkAddr(0x30,53,5);
  lcd_writeChunkAddr(0xff,53,4);
  lcd_writeChunkAddr(0xef,53,3);
  lcd_writeChunkAddr(0xff,53,2);
  lcd_writeChunkAddr(0x30,53,0);

  lcd_writeChunkAddr(0xe7,54,7);
  lcd_writeChunkAddr(0xf3,54,6);
  lcd_writeChunkAddr(0x31,54,5);
  lcd_writeChunkAddr(0xff,54,4);
  lcd_writeChunkAddr(0xff,54,3);
  lcd_writeChunkAddr(0xff,54,2);
  lcd_writeChunkAddr(0x30,54,0);

  lcd_writeChunkAddr(0xef,55,7);
  lcd_writeChunkAddr(0x33,55,5);
  lcd_writeChunkAddr(0xff,55,4);
  lcd_writeChunkAddr(0xe3,55,3);
  lcd_writeChunkAddr(0xff,55,2);
  lcd_writeChunkAddr(0x30,55,0);

  lcd_writeChunkAddr(0x1,56,8);
  lcd_writeChunkAddr(0xcf,56,7);
  lcd_writeChunkAddr(0x37,56,5);
  lcd_writeChunkAddr(0xff,56,4);
  lcd_writeChunkAddr(0xe0,56,3);
  lcd_writeChunkAddr(0x7f,56,2);
  lcd_writeChunkAddr(0x30,56,0);

  lcd_writeChunkAddr(0x1,57,8);
  lcd_writeChunkAddr(0xcf,57,7);
  lcd_writeChunkAddr(0x0c,57,6);
  lcd_writeChunkAddr(0x37,57,5);
  lcd_writeChunkAddr(0xff,57,4);
  lcd_writeChunkAddr(0xc0,57,3);
  lcd_writeChunkAddr(0x0f,57,2);
  lcd_writeChunkAddr(0xf3,57,1);
  lcd_writeChunkAddr(0x30,57,0);

  lcd_writeChunkAddr(0x3,58,8);
  lcd_writeChunkAddr(0x8f,58,7);
  lcd_writeChunkAddr(0x0c,58,6);
  lcd_writeChunkAddr(0x3f,58,5);
  lcd_writeChunkAddr(0xff,58,4);
  lcd_writeChunkAddr(0x80,58,3);
  lcd_writeChunkAddr(0x1f,58,2);
  lcd_writeChunkAddr(0xf3,58,1);
  lcd_writeChunkAddr(0x30,58,0);

  lcd_writeChunkAddr(0x3,59,8);
  lcd_writeChunkAddr(0x8f,59,7);
  lcd_writeChunkAddr(0xff,59,6);
  lcd_writeChunkAddr(0xff,59,5);
  lcd_writeChunkAddr(0xff,59,4);
  lcd_writeChunkAddr(0x1f,59,2);
  lcd_writeChunkAddr(0x30,59,0);

  lcd_writeChunkAddr(0x3,60,8);
  lcd_writeChunkAddr(0x8f,60,7);
  lcd_writeChunkAddr(0xff,60,6);
  lcd_writeChunkAddr(0xf1,60,5);
  lcd_writeChunkAddr(0xff,60,4);
  lcd_writeChunkAddr(0x3f,60,2);
  lcd_writeChunkAddr(0x30,60,0);

  lcd_writeChunkAddr(0x7,61,8);
  lcd_writeChunkAddr(0x7f,61,6);
  lcd_writeChunkAddr(0xf0,61,5);
  lcd_writeChunkAddr(0x3e,61,4);
  lcd_writeChunkAddr(0x7f,61,2);
  lcd_writeChunkAddr(0x30,61,0);

  lcd_writeChunkAddr(0x7,62,8);
  lcd_writeChunkAddr(0xc0,62,7);
  lcd_writeChunkAddr(0x7f,62,6);
  lcd_writeChunkAddr(0xe0,62,5);
  lcd_writeChunkAddr(0x07,62,4);
  lcd_writeChunkAddr(0xff,62,2);
  lcd_writeChunkAddr(0x30,62,0);

  lcd_writeChunkAddr(0x7,63,8);
  lcd_writeChunkAddr(0xf8,63,7);
  lcd_writeChunkAddr(0x7f,63,6);
  lcd_writeChunkAddr(0xe0,63,5);
  lcd_writeChunkAddr(0x07,63,4);
  lcd_writeChunkAddr(0xe0,63,3);
  lcd_writeChunkAddr(0xff,63,2);
  lcd_writeChunkAddr(0xff,63,1);
  lcd_writeChunkAddr(0xf0,63,0);

  lcd_writeChunkAddr(0x7,64,8);
  lcd_writeChunkAddr(0xff,64,7);
  lcd_writeChunkAddr(0xff,64,6);
  lcd_writeChunkAddr(0xc0,64,5);
  lcd_writeChunkAddr(0x07,64,4);
  lcd_writeChunkAddr(0xfd,64,3);
  lcd_writeChunkAddr(0xff,64,2);
  lcd_writeChunkAddr(0xff,64,1);
  lcd_writeChunkAddr(0xf0,64,0);

  lcd_writeChunkAddr(0x7,65,8);
  lcd_writeChunkAddr(0xff,65,7);
  lcd_writeChunkAddr(0xff,65,6);
  lcd_writeChunkAddr(0xc0,65,5);
  lcd_writeChunkAddr(0x0f,65,4);
  lcd_writeChunkAddr(0xff,65,3);
  lcd_writeChunkAddr(0xff,65,2);
  lcd_writeChunkAddr(0xff,65,1);
  lcd_writeChunkAddr(0x80,65,0);

  lcd_writeChunkAddr(0x7,66,8);
  lcd_writeChunkAddr(0xff,66,7);
  lcd_writeChunkAddr(0xbf,66,6);
  lcd_writeChunkAddr(0xc0,66,5);
  lcd_writeChunkAddr(0x0f,66,4);
  lcd_writeChunkAddr(0xff,66,3);
  lcd_writeChunkAddr(0xff,66,2);
  lcd_writeChunkAddr(0xff,66,1);
  lcd_writeChunkAddr(0x80,66,0);

  lcd_writeChunkAddr(0x7,67,8);
  lcd_writeChunkAddr(0xff,67,7);
  lcd_writeChunkAddr(0x87,67,6);
  lcd_writeChunkAddr(0x80,67,5);
  lcd_writeChunkAddr(0x1f,67,4);
  lcd_writeChunkAddr(0xff,67,3);
  lcd_writeChunkAddr(0xf8,67,2);
  lcd_writeChunkAddr(0x01,67,1);
  lcd_writeChunkAddr(0x80,67,0);

  lcd_writeChunkAddr(0x7,68,8);
  lcd_writeChunkAddr(0xff,68,7);
  lcd_writeChunkAddr(0x80,68,6);
  lcd_writeChunkAddr(0xf0,68,5);
  lcd_writeChunkAddr(0x1f,68,4);
  lcd_writeChunkAddr(0xff,68,3);
  lcd_writeChunkAddr(0x78,68,2);
  lcd_writeChunkAddr(0x01,68,1);
  lcd_writeChunkAddr(0x80,68,0);

  lcd_writeChunkAddr(0x7,69,8);
  lcd_writeChunkAddr(0xff,69,7);
  lcd_writeChunkAddr(0x80,69,6);
  lcd_writeChunkAddr(0xfe,69,5);
  lcd_writeChunkAddr(0x1f,69,4);
  lcd_writeChunkAddr(0xff,69,3);
  lcd_writeChunkAddr(0x78,69,2);
  lcd_writeChunkAddr(0x01,69,1);
  lcd_writeChunkAddr(0x80,69,0);

  lcd_writeChunkAddr(0x7,70,8);
  lcd_writeChunkAddr(0xff,70,7);
  lcd_writeChunkAddr(0x80,70,6);
  lcd_writeChunkAddr(0xff,70,5);
  lcd_writeChunkAddr(0xff,70,4);
  lcd_writeChunkAddr(0xfe,70,3);
  lcd_writeChunkAddr(0x78,70,2);
  lcd_writeChunkAddr(0x01,70,1);
  lcd_writeChunkAddr(0x80,70,0);

  lcd_writeChunkAddr(0x7,71,8);
  lcd_writeChunkAddr(0xff,71,7);
  lcd_writeChunkAddr(0x80,71,6);
  lcd_writeChunkAddr(0xff,71,5);
  lcd_writeChunkAddr(0xff,71,4);
  lcd_writeChunkAddr(0xfe,71,3);
  lcd_writeChunkAddr(0x79,71,2);
  lcd_writeChunkAddr(0xf9,71,1);
  lcd_writeChunkAddr(0x80,71,0);

  lcd_writeChunkAddr(0x7,72,8);
  lcd_writeChunkAddr(0x3f,72,7);
  lcd_writeChunkAddr(0x80,72,6);
  lcd_writeChunkAddr(0xff,72,5);
  lcd_writeChunkAddr(0xe7,72,4);
  lcd_writeChunkAddr(0xfe,72,3);
  lcd_writeChunkAddr(0x79,72,2);
  lcd_writeChunkAddr(0xf9,72,1);
  lcd_writeChunkAddr(0x80,72,0);

  lcd_writeChunkAddr(0x7,73,8);
  lcd_writeChunkAddr(0x07,73,7);
  lcd_writeChunkAddr(0x81,73,6);
  lcd_writeChunkAddr(0xff,73,5);
  lcd_writeChunkAddr(0xe0,73,4);
  lcd_writeChunkAddr(0xfc,73,3);
  lcd_writeChunkAddr(0x79,73,2);
  lcd_writeChunkAddr(0xf9,73,1);
  lcd_writeChunkAddr(0x80,73,0);

  lcd_writeChunkAddr(0x3,74,8);
  lcd_writeChunkAddr(0x80,74,7);
  lcd_writeChunkAddr(0xe0,74,6);
  lcd_writeChunkAddr(0xff,74,5);
  lcd_writeChunkAddr(0xe0,74,4);
  lcd_writeChunkAddr(0x1c,74,3);
  lcd_writeChunkAddr(0x79,74,2);
  lcd_writeChunkAddr(0xf9,74,1);
  lcd_writeChunkAddr(0x80,74,0);

  lcd_writeChunkAddr(0x3,75,8);
  lcd_writeChunkAddr(0x80,75,7);
  lcd_writeChunkAddr(0xf8,75,6);
  lcd_writeChunkAddr(0xff,75,5);
  lcd_writeChunkAddr(0xe0,75,4);
  lcd_writeChunkAddr(0x1c,75,3);
  lcd_writeChunkAddr(0x79,75,2);
  lcd_writeChunkAddr(0xf9,75,1);
  lcd_writeChunkAddr(0x80,75,0);


  lcd_writeChunkAddr(0x3,76,8);
  lcd_writeChunkAddr(0x80,76,7);
  lcd_writeChunkAddr(0xff,76,6);
  lcd_writeChunkAddr(0xff,76,5);
  lcd_writeChunkAddr(0xe0,76,4);
  lcd_writeChunkAddr(0x1c,76,3);
  lcd_writeChunkAddr(0x79,76,2);
  lcd_writeChunkAddr(0xf9,76,1);
  lcd_writeChunkAddr(0x80,76,0);

  lcd_writeChunkAddr(0x3,77,8);
  lcd_writeChunkAddr(0x80,77,7);
  lcd_writeChunkAddr(0x7f,77,6);
  lcd_writeChunkAddr(0xff,77,5);
  lcd_writeChunkAddr(0xe0,77,4);
  lcd_writeChunkAddr(0x1c,77,3);
  lcd_writeChunkAddr(0x7f,77,2);
  lcd_writeChunkAddr(0xff,77,1);
  lcd_writeChunkAddr(0x80,77,0);

  lcd_writeChunkAddr(0x1,78,8);
  lcd_writeChunkAddr(0xc0,78,7);
  lcd_writeChunkAddr(0x7f,78,6);
  lcd_writeChunkAddr(0x8f,78,5);
  lcd_writeChunkAddr(0xe0,78,4);
  lcd_writeChunkAddr(0x1c,78,3);
  lcd_writeChunkAddr(0x7f,78,2);
  lcd_writeChunkAddr(0xff,78,1);
  lcd_writeChunkAddr(0x80,78,0);

  lcd_writeChunkAddr(0x1,79,8);
  lcd_writeChunkAddr(0xc0,79,7);
  lcd_writeChunkAddr(0x7f,79,6);
  lcd_writeChunkAddr(0x81,79,5);
  lcd_writeChunkAddr(0xe0,79,4);
  lcd_writeChunkAddr(0x1f,79,3);
  lcd_writeChunkAddr(0xff,79,2);
  lcd_writeChunkAddr(0xfc,79,1);

  lcd_writeChunkAddr(0x1,80,8);
  lcd_writeChunkAddr(0xc0,80,7);
  lcd_writeChunkAddr(0x7f,80,6);
  lcd_writeChunkAddr(0xc0,80,5);
  lcd_writeChunkAddr(0x38,80,4);
  lcd_writeChunkAddr(0x1f,80,3);
  lcd_writeChunkAddr(0xff,80,2);
  lcd_writeChunkAddr(0xfc,80,1);

  lcd_writeChunkAddr(0xf0,81,7);
  lcd_writeChunkAddr(0x3f,81,6);
  lcd_writeChunkAddr(0xc0,81,5);
  lcd_writeChunkAddr(0x3f,81,4);
  lcd_writeChunkAddr(0x1f,81,3);
  lcd_writeChunkAddr(0xc0,81,2);
  lcd_writeChunkAddr(0x0c,81,1);

  lcd_writeChunkAddr(0xfe,82,7);
  lcd_writeChunkAddr(0x3f,82,6);
  lcd_writeChunkAddr(0xc0,82,5);
  lcd_writeChunkAddr(0x3f,82,4);
  lcd_writeChunkAddr(0xff,82,3);
  lcd_writeChunkAddr(0xc0,82,2);
  lcd_writeChunkAddr(0x0c,82,1);

  lcd_writeChunkAddr(0x3f,83,7);
  lcd_writeChunkAddr(0xff,83,6);
  lcd_writeChunkAddr(0xc0,83,5);
  lcd_writeChunkAddr(0x1f,83,4);
  lcd_writeChunkAddr(0xff,83,3);
  lcd_writeChunkAddr(0xc0,83,2);
  lcd_writeChunkAddr(0x0c,83,1);

  lcd_writeChunkAddr(0x0f,84,7);
  lcd_writeChunkAddr(0xff,84,6);
  lcd_writeChunkAddr(0xe0,84,5);
  lcd_writeChunkAddr(0x1f,84,4);
  lcd_writeChunkAddr(0xff,84,3);
  lcd_writeChunkAddr(0xc0,84,2);
  lcd_writeChunkAddr(0x0c,84,1);

  lcd_writeChunkAddr(0x01,85,7);
  lcd_writeChunkAddr(0xff,85,6);
  lcd_writeChunkAddr(0xe0,85,5);
  lcd_writeChunkAddr(0x1f,85,4);
  lcd_writeChunkAddr(0xff,85,3);
  lcd_writeChunkAddr(0xcc,85,2);
  lcd_writeChunkAddr(0xcc,85,1);

  lcd_writeChunkAddr(0x3f,86,6);
  lcd_writeChunkAddr(0xe0,86,5);
  lcd_writeChunkAddr(0x1f,86,4);
  lcd_writeChunkAddr(0xff,86,3);
  lcd_writeChunkAddr(0xcc,86,2);
  lcd_writeChunkAddr(0xcc,86,1);

  lcd_writeChunkAddr(0x07,87,6);
  lcd_writeChunkAddr(0xfc,87,5);
  lcd_writeChunkAddr(0x0f,87,4);
  lcd_writeChunkAddr(0xff,87,3);
  lcd_writeChunkAddr(0xcc,87,2);
  lcd_writeChunkAddr(0xcc,87,1);

  lcd_writeChunkAddr(0x01,88,6);
  lcd_writeChunkAddr(0xff,88,5);
  lcd_writeChunkAddr(0x8f,88,4);
  lcd_writeChunkAddr(0xff,88,3);
  lcd_writeChunkAddr(0xcc,88,2);
  lcd_writeChunkAddr(0xcc,88,1);

  lcd_writeChunkAddr(0x3f,89,5);
  lcd_writeChunkAddr(0xff,89,4);
  lcd_writeChunkAddr(0xff,89,3);
  lcd_writeChunkAddr(0xcf,89,2);
  lcd_writeChunkAddr(0xcc,89,1);

  lcd_writeChunkAddr(0x03,90,5);
  lcd_writeChunkAddr(0xff,90,4);
  lcd_writeChunkAddr(0xff,90,3);
  lcd_writeChunkAddr(0xcf,90,2);
  lcd_writeChunkAddr(0xcc,90,1);

  lcd_writeChunkAddr(0x7f,91,4);
  lcd_writeChunkAddr(0xff,91,3);
  lcd_writeChunkAddr(0xfc,91,2);
  lcd_writeChunkAddr(0xfc,91,1);

  lcd_writeChunkAddr(0x0f,92,4);
  lcd_writeChunkAddr(0xff,92,3);
  lcd_writeChunkAddr(0xfc,92,2);
  lcd_writeChunkAddr(0xfc,92,1);

  lcd_writeChunkAddr(0x01,93,4);
  lcd_writeChunkAddr(0xff,93,3);

  lcd_writeChunkAddr(0x3f,94,3);
  lcd_writeChunkAddr(0x80,94,2);

  lcd_writeChunkAddr(0x0f,95,3);
  lcd_writeChunkAddr(0x80,95,2);


}


