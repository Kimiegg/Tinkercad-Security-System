#include <Servo.h>
#include <LiquidCrystal.h>
#include <Wire.h>


Servo myservo;
int pos = 0;
//////////////////////////////////////////////
const int rs = 2, en = 3, d4 = 5, d5 = 4, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int LineNumber = 1;
int Cursor = 0;
char * textToDisplay = " Input your passcode to open the door!                ";
int RoW = 3;
int unlockedSystem = 1; //1=false
///////////////////////////////////////////////



void setup()
{
  pinMode(8,INPUT);
  pinMode(10,OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor (0,0);
  lcd.print ("Important :"); 
///////////////////////////////////
  Wire.begin(1);
  Wire.onReceive(recieveEvent);
  Serial.begin(9600);
  //////////////////////////
  myservo.attach(9);
  myservo.write(0);
  //ServoClose();
  
}

void loop()
{
  int pirResult = digitalRead(8);
  Serial.println(pirResult);
  if(unlockedSystem == 1 && pirResult == 1)
  {
  		textToDisplay = "Intruder Alert!  ";
  		lcd.setCursor (0,1);
    	lcd.print(textToDisplay);
    	tone(13,800,250);
  }
  
  else if(unlockedSystem == 1)
  {
     if(RoW == 0)
  	 {
  		textToDisplay = "    Correct!    ";
  		lcd.setCursor (0,1);
    	lcd.print(textToDisplay);
       	delay(1500);
       	RoW = 5;
  	 }
    else if (RoW == 5)
    {
    	textToDisplay = "  Welcome home!  ";
       	lcd.setCursor (0,1);
    	lcd.print(textToDisplay);
      	unlockedSystem = 0;
      
    }
    
  else if (RoW == 1)
  {
    textToDisplay = "   Incorrect!   ";
  	lcd.setCursor (0,1);
    lcd.print(textToDisplay);
    RoW = 3;
    delay(2500);
  }
    else
    {
    textToDisplay = " Input your passcode to open the door!                ";
    UpdateLCDDisplay();
  	delay(100);	
    }
    
  }
  
  else if(unlockedSystem == 0)
  {
  	myservo.write(90);
  }
  
  
}



void recieveEvent(int howMany)
{
	RoW = Wire.read();
  	
 	
  	Serial.println(RoW);
}



////////////////////////////LCD//////////////////////
void UpdateLCDDisplay()
{
 int LenghtOfText = strlen(textToDisplay);
  if( Cursor == (LenghtOfText - 1))
  {
  	Cursor = 0;
  }
  lcd.setCursor(0, LineNumber);
    if (Cursor < LenghtOfText - 16)
  {
    for (int Char = Cursor; Char < Cursor +16; Char++)
    {
    	lcd.print(textToDisplay[Char]);
    }
  }
  else
  {
  	for (int Char = Cursor; Char < (LenghtOfText - 1); Char++)
    {
    	lcd.print(textToDisplay[Char]);
    }
    
    for (int Char = 0; Char <= 16 - (LenghtOfText - Cursor); Char++)
    {
    	lcd.print(textToDisplay[Char]);
    }
  }
  Cursor++;
}