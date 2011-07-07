#include <Button.h> 
#include <FancySolenoid.h> 

bool debugFlag = 0;

const byte numberOfthwackers = 8;
byte thwackPinArray[numberOfthwackers] = { 
  2,3,4,5,6, 7, 8,9 } 
;

//the pit array of the pinstates for the thwackers
unsigned char thwackMe = 0;
//Instantiate Button on digital pin 2
//pressed = ground (pulled high with _external_ resistor)
Button helloButton = Button(11, LOW);

//Instantiate FancySolenoid on digital pin 5
//active = HIGH (could need to be low if inverting IC is being used...)  
//since thwackPinArray[3] is PIN 5 in this instantiation style
//we use 3 ("third bit in register")
FancySolenoid testSolenoid = FancySolenoid(3, HIGH, &thwackMe);


void setup()
{
  Serial.begin(9600);
  testSolenoid.setFullPeriod(1000);
  testSolenoid.setDutyCycle(40);

  //have to do outputs b/c using the solenoid register style
  for (byte i = 0; i <= numberOfthwackers; i ++) {
    pinMode(thwackPinArray[i], OUTPUT);
  }


}

void loop()
{

  helloButton.listen();  
  testSolenoid.update();

  if (helloButton.onPress()) {
    //will pulse once at current duty cycle and period settings
    // testSolenoid.pulse();

    //will pulse 5 times at current duty cycle and period settings
    testSolenoid.pulse(5);

    //will pulse once and update duty cycle and period settings
    //testSolenoid.pulse(2000, 10);

    //will pulse 5 times and update duty cycle and period settings
    //testSolenoid.pulse(5, 2000, 10);


    Serial.println(testSolenoid.getFullPeriod());
    Serial.println(testSolenoid.getDutyCycle());
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
    Serial.println(myDataOut, DEC);
  }
}
