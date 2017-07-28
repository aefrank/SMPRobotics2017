

#include <TobiPro.h>


/*          SERIALSETUP()
    Set up Serial communication. Begins Serial communication at 9600 baud, sets timeout at
    10 ms, waits 5 seconds for Serial comm to begin before returning and allowing program
    to continue.
    INPUTS:   - None.
    OUTPUTS:  - None.
    UPDATES:  - None.
    EFFECTS:  - Serial communication set up.
*/
void serialSetup(){
  // Set up Serial Communication
  Serial.begin(9600);
  Serial.setTimeout(10);
  int i = 0; int waitTime = 500; // wait 5 seconds; if Serial comm isn't started by then, move on
  while(!Serial && i < waitTime) { i++; delay(10); }  // each loop = 0.01 second
}


//************************** CLASS METHODS ***************************//
TobiPro::TobiPro(){
  for(int i = 0; i < NUM_MOTORS; i++){
    TobiPro::_motorIndices[i] = i;
  }
  for (int i = 0; i < MAX_NUM_MOTORS; i++){
    TobiPro::_motorSpeed[i] = 0;
  }

  TobiPro::filterInputs(true);
}


void TobiPro::setMotorIndices(int* motInd){
    for(int i = 0; i < NUM_MOTORS; i++){
      TobiPro::_motorIndices[i] = motInd[i];
    }
}

void TobiPro::filterInputs(bool onOff){
    TobiPro::filter.onOff(onOff);
}

void TobiPro::update(){
  for (int i = 0; i < NUM_MOTORS; i++){
      TobiPro::_motorSpeed[TobiPro::_motorIndices[i]] = TobiPro::calcSpeed(i); // calc speed; also updates filters
  }
}

void TobiPro::srDelay(){
  delay(TobiPro::_dt);
}


int TobiPro::getSpeed(int motor){
  return TobiPro::_motorSpeed[motor];
}

/*          CALCSPEED() 
    Get the speed of a particular motor. Returns filtered speed if filter is on, and raw speed if filter
    is off. The speed is returned in units of change in encoder values per second.
    INPUTS:   - int motor
    OUTPUTS:  - int rawSpeed
    UPDATES:  - None.
    EFFECTS:  - None.
*/
int TobiPro::calcSpeed(int motor){
    
    // read encoder of desired motor
    int thisVal = TobiPro::readEncoder(motor);
    float thisTime = getTime();

    // get last motor value and update last values
    int lastVal = TobiPro::_lastEnc[motor];
    float lastTime = TobiPro::_lastTime[motor];
    TobiPro::_lastEnc[motor] = thisVal;
    TobiPro::_lastTime[motor] = thisTime;

    int maxVal = TobiPro::maxEncoderVals[motor];
    
    int rawSpeed;
     // edge cases -- if rolled over, just use last speed
    if ( fabs(lastVal-thisVal) > abs(lastVal)*0.25)        rawSpeed = TobiPro::_motorSpeed[motor];       
    else                                                   rawSpeed = (thisVal - lastVal)/(thisTime - lastTime);

    // update filter, even if off
    TobiPro::filter.input(motor, rawSpeed);

    if(TobiPro::filter.isOn(motor))           return TobiPro::filter.output(motor);
    else                                      return rawSpeed;
}

void TobiPro::setSampleRate(int dtInMs){
  TobiPro::_dt = dtInMs;
}

void TobiPro::setSpeed(int motor, float percent){
  int pwm = (int)(percent * 2.55);
  TobiPro::setPwm(motor, pwm);
}
