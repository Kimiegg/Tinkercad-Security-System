#include <Keypad.h>
#include <Wire.h>

#define passLenght 7
char Code[passLenght];
char Pwd[passLenght] = "271104";

byte pressedKeysNum = 0;

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {12, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customkeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup()
{
  Wire.begin();
  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  Wire.beginTransmission(1);
  char customKey = customkeypad.getKey();
  if(customKey)
  {
  	//Serial.println(customKey);
    Code[pressedKeysNum] = customKey;
    Serial.print(Code[pressedKeysNum]);
    pressedKeysNum++;
    
  }
  
  if(pressedKeysNum == passLenght-1)
  {
  	Serial.println(" ");
    
    if(!strcmp(Pwd, Code))
    {
    	Serial.println("Correct");
      	int RoW = 0;
      	Wire.write(RoW);
      	Wire.endTransmission();
      	analogWrite(9, 255);
    	analogWrite(10, 128);
    	analogWrite(11, 43);
      	delay(10);
      	analogWrite(9, LOW);
    	analogWrite(10, LOW);
    	analogWrite(11, LOW);
     	delay(10);
      	analogWrite(9, 255);
    	analogWrite(10, 128);
    	analogWrite(11, 43);
      	delay(10);
      	analogWrite(9, LOW);
    	analogWrite(10, LOW);
    	analogWrite(11, LOW);
      	delay(10);
      	analogWrite(9, 255);
    	analogWrite(10, 128);
    	analogWrite(11, 43);
      	delay(10);
      	analogWrite(9, LOW);
    	analogWrite(10, LOW);
    	analogWrite(11, LOW);
      	
      delay(4000);
    }
    
    else
    {
      	Serial.println("Incorrect");
      	int RoW = 1;
      	Wire.write(RoW);
      	Wire.endTransmission();
      	analogWrite(9, 36);
    	analogWrite(10, 102);
    	analogWrite(11, 255);
      	delay(350);
      	analogWrite(9, LOW);
    	analogWrite(10, LOW);
    	analogWrite(11, LOW);
     	
      delay(1000);
    }
    
    DeleteCount();
  }
    
    
  //tone(13,600,50);
  //delay(1000);
}


void DeleteCount()
{
  while(pressedKeysNum !=0)
  {
   Code[pressedKeysNum--]=0;
  }
  return;
}