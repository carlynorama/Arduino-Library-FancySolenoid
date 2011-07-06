/*
	FancySolenoid.h - - FancySolenoid library for Wiring/Arduino - Version 0.1
	
	Original library 		(0.1) by Carlyn Maw.
	
 */

// ensure this library description is only included once
#ifndef FancySolenoid_h
#define FancySolenoid_h

// include types & constants of Wiring core API
#include "WProgram.h"

// library interface description
class FancySolenoid {
 
  // user-accessible "public" interface
  public:
  // constructors:
    FancySolenoid(int myPin, bool myMode);
    FancySolenoid(int myBit, bool myMode, unsigned char *myRegister);
    
    //char* version(void);			// get the library version
    //unsigned char getRegisterValue(void);

    void setCurrentTime(unsigned long);
    void update(unsigned long);
    void update(void);
    
    int getState(void);
    
    void turnOn(void);	
    void turnOff(void);
 
    void pulse(char); 
    void pulse(char, int, int);

	void pulse(void);	
	void pulse(int, int);

	
	int getDutyCycle(void);
	void setDutyCycle(int);
	
	long getFullPeriod(void);
	void setFullPeriod(long);

    


  // library-accessible "private" interface
  private:
    int _myPin;
    int _myBit;
    unsigned char *_myRegister;
    unsigned char _registerValue;
    bool _type;  //direct pin or shift register
    bool _mode;  //HIGH == pressed (1) or LOW == pressed (0)
    
    int _lastState;
    int _currentState;
    bool _pinState;
    
    int _onPeriod;
    int _offPeriod;
    int _dutyCycle;
    long _fullPeriod;
   //long _longHolder;
        		
    bool _pulseFlag;    		

    unsigned long int _flipTime;	
	unsigned long int _currentTime;
	
	int _currentPulseCount;
	int _goalPulseCount;

	
	void updatePin(bool);
  
};

#endif

