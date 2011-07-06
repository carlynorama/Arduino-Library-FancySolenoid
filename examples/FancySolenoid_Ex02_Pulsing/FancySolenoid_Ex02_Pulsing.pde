
#include <Button.h> 
#include <FancySolenoid.h> 

unsigned long  loopCurrentTime = 0;

  //Instantiate Button on digital pin 2
  //pressed = ground (pulled high with _external_ resistor)
  Button helloButton = Button(11, LOW);
     
  //Instantiate FancySolenoid on digital pin 5
  //active = HIGH (could need to be low if inverting IC is being used...)  
  FancySolenoid potSolenoid = FancySolenoid(5, HIGH);


void setup()
{
  Serial.begin(9600);
  potSolenoid.setFullPeriod(1000);
  potSolenoid.setDutyCycle(10);
  
}

void loop()
{

  helloButton.listen();  
  potSolenoid.update();

  if (helloButton.onPress()) {
    //will pulse once at current duty cycle and period settings
    // potSolenoid.pulse();
    
    //will pulse 5 times at current duty cycle and period settings
    potSolenoid.pulse(5);
    
    //will pulse once and update duty cycle and period settings
    //potSolenoid.pulse(2000, 10);
   
    //will pulse 5 times and update duty cycle and period settings
    //potSolenoid.pulse(5, 2000, 10);

    
    Serial.println(potSolenoid.getFullPeriod());
    Serial.println(potSolenoid.getDutyCycle());
  } 

}

