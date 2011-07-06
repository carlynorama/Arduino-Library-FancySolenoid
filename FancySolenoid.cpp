/*
  FancySolenoid.h - FancySolenoid for Wiring/Arduino
  (cc) 2011 Carlyn Maw, Attribute, Share Alike
  
  Created 06 July 2011
  Version 0.1
*/


// include core Wiring API
#include "WProgram.h"

// include this library's description file
#include "FancySolenoid.h"

   
  
// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

//------------------------------------------------------ Using Arduino Pin Num
FancySolenoid::FancySolenoid(int myPin, bool myMode)
{
    // initialize this instance's variables
    this->_myPin = myPin;
    
    pinMode(this->_myPin, OUTPUT);
    
    this->_type = 0;
    this->_myBit = this->_myPin;
    this->_mode = myMode;
    
    _lastState = 0;
    _currentState = 0;
    _pinState= 0;
    
    _dutyCycle = 10;
    _fullPeriod = 2000;
      
}

//----------------------------------------------------------------- Using Byte
FancySolenoid::FancySolenoid(int myBit, bool myMode, unsigned char *myRegister)
{
    // initialize this instance's variables
    this->_type = 1;
    this->_mode = myMode;
    this->_myBit = myBit;
    this->_myPin = this->_myBit;  
    this->_myRegister = myRegister;
    
    this->_registerValue = 255;
    
    _lastState = 0;
    _currentState = 0;
    _pinState= 0;
    
    _dutyCycle = 10;
    _fullPeriod = 1000;
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

//---------////////////////////MAIN LOOP / LISTENER ///////////--------------//

void FancySolenoid::update(void) {
           update(millis());
}



void FancySolenoid::update(unsigned long newCurrentTime) {
      _currentTime = newCurrentTime;
      
      if (_currentPulseCount < _goalPulseCount) {
         _pulseFlag = true;
      } else if (_currentPulseCount >= _goalPulseCount) {
      }
      
      
      // if (_pulseFlag && _countFlag) {
      if (_pulseFlag) {
        //_longHolder = (_fullPeriod * _dutyCycle) / 100;
        //_onPeriod = int(_longHolder);
         _onPeriod = (_fullPeriod * _dutyCycle) / 100;
        _offPeriod = (_fullPeriod - _onPeriod);
        //Serial.println(_onPeriod);

      //if my state is ready 
      if (_currentState == 0) {
        //get the time
        _flipTime = _currentTime;
        //set my state to firing
        _currentState = 1;
        //turn on the pin
        _pinState = _mode;
        updatePin(_pinState);
      } 
      //if my state is firing
      else if (_currentState == 1) { 
        if ((_onPeriod) < (_currentTime - _flipTime)) {
          //if it's time, turn me off
          _flipTime = _currentTime;
          _currentState = 2;
          _pinState = !_mode;
          updatePin(_pinState);
        }    
      } 
      //if my state is resting
      else if (_currentState == 2) {
        //keep me off
        _pinState = !_mode;
        updatePin(_pinState);
        //check the time and make me ready
        if ((_offPeriod) < (_currentTime - _flipTime)) {
          _currentState = 0;
          _currentPulseCount++;
          _pulseFlag = false;
          _flipTime = _currentTime;
        }
    
      }
    }
}


void FancySolenoid::setCurrentTime(unsigned long newCurrentTime) {
    _currentTime = newCurrentTime;
}

int FancySolenoid::getState(void){
    return _currentState;
}



void FancySolenoid::turnOn(void){
    _pinState = _mode;
    updatePin(_pinState);
    
	_lastState = _currentState;
	_currentState = 1; //firing
    _flipTime = _currentTime;

}

void FancySolenoid::turnOff(void){
    _pinState = !_mode;
    updatePin(_pinState);

	_lastState = _currentState;
	_currentState = 2; //waiting

}

void FancySolenoid::pulse(char myPulseTimes) {

    _pulseFlag = true;
    _goalPulseCount = myPulseTimes;
    _currentPulseCount = 0;
    
}

void FancySolenoid::pulse(char myPulseTimes, int myPeriod, int myDutyCycle) {

    _dutyCycle = myDutyCycle;
    _fullPeriod = myPeriod;
    pulse(myPulseTimes);
    
}

void FancySolenoid::pulse(void) {

    pulse(1);
    
}

void FancySolenoid::pulse(int myPeriod, int myDutyCycle) {

    pulse(1, myPeriod, myDutyCycle);
    
}

int FancySolenoid::getDutyCycle(void){
    return _dutyCycle;
}

void FancySolenoid::setDutyCycle(int newDC) {
    _dutyCycle = newDC;
}

long FancySolenoid::getFullPeriod(void){
    return _fullPeriod;
}

void FancySolenoid::setFullPeriod(long newFP){
    _fullPeriod = newFP;
}

// Private Methods //////////////////////////////////////////////////////////////
// Functions available to the library only.


void FancySolenoid::updatePin(bool pinValue) {
    if (pinValue) {
        digitalWrite(_myPin, HIGH);
    } else {
        digitalWrite(_myPin, LOW);
    }

}
