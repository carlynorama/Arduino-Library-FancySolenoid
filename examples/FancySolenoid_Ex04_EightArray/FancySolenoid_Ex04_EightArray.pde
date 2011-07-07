#include <Button.h> 
#include <FancySolenoid.h> 

bool debugFlag = 0;
unsigned long currentTime = 0;

const byte numberOfthwackers = 8;
byte thwackPinArray[numberOfthwackers] = { 
  2, 3,4 ,5 ,6, 7, 8,9 } 
;

//the pit array of the pinstates for the thwackers
unsigned char thwackMe = 0;
//Instantiate Button on digital pin 2
//pressed = ground (pulled high with _external_ resistor)
Button helloButton = Button(11, LOW);

FancySolenoid solenoids[numberOfthwackers] = { 
  FancySolenoid(0, HIGH, &thwackMe), 
  FancySolenoid(1, HIGH, &thwackMe), 
  FancySolenoid(2, HIGH, &thwackMe),
  FancySolenoid(3, HIGH, &thwackMe), 
  FancySolenoid(4, HIGH, &thwackMe), 
  FancySolenoid(5, HIGH, &thwackMe),
  FancySolenoid(6, HIGH, &thwackMe), 
  FancySolenoid(7, HIGH, &thwackMe)
  };


  void setup()
  {
    Serial.begin(9600);


    //have to do outputs b/c using the solenoid register style
    for (byte i = 0; i < numberOfthwackers; i ++) {
      pinMode(thwackPinArray[i], OUTPUT);
    }


  }

void loop()
{

  helloButton.listen();  

  currentTime = millis();

  for (byte i = 0; i < numberOfthwackers; i ++) {
    solenoids[i].update(currentTime);
  }


  if (helloButton.onPress()) {
    
    for (byte i = 0; i < numberOfthwackers; i ++) {
      solenoids[i].pulse(5);
    }
    
  }

  thwackOut(thwackMe);
}


void thwackOut(byte myDataOut) {
  int pinState;
  for (int t=7; t>=0; t--)  {
    if ( myDataOut & (1<<t) ) {
      pinState= 1;
    }
    else {	
      pinState= 0;
    }
    digitalWrite(thwackPinArray[t], pinState);
  }
  if (debugFlag) {
    Serial.println(myDataOut, BIN);
  }
}


