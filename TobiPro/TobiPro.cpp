

#include <TobiPro.h>

//************************** LIBRARY METHODS ***************************//
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
/*      CONSTRUCTOR
    Creates a new TobiPro object. TobiPro is an extension of the Tobi class from Tobi.h.
    Sets motor indices to 0 to NUM_MOTORS as default; motor speeds to 0, and filters to on.
*/
TobiPro::TobiPro(){
  for(int i = 0; i < NUM_MOTORS; i++){
    TobiPro::_motorIndices[i] = i;
  }
  for (int i = 0; i < MAX_NUM_MOTORS; i++){
    TobiPro::_motorSpeed[i] = 0;
  }

  TobiPro::filterInputs(true);
}

/*      SETMOTORINDICES()
    If active motors are not numbered simply 0 through NUM_MOTORS, this method can be used to
    set TobiPro::_motorIndices to the correct indices for the active motors.
    INPUTS:   - int* motInd (pointer to an integer array of size NUM_MOTORS corresponding to
                    the motors that are active for this TobiPro).
    OUTPUTS:  - None.
    UPDATES:  - TobiPro::_motorIndices
    EFFECTS:  - None.
*/
void TobiPro::setMotorIndices(int* motInd){
    for(int i = 0; i < NUM_MOTORS; i++){
      TobiPro::_motorIndices[i] = motInd[i];
    }
}

/*      FILTERINPUTS()
    Sets TobiPro to filter or not filter encoder values with a two pole low pass filter, defined
    in TobiFilterManager.
    INPUTS:   - bool onOff (true for filtering on, false for filtering off).
    OUTPUTS:  - None.
    UPDATES:  - TobiPro::filter.
    EFFECTS:  - None.
*/
void TobiPro::filterInputs(bool onOff){
    TobiPro::filter.onOff(onOff);
}


/*      UPDATE()
    Calculates speed and updates filters for each motor.
    INPUTS:   - None.
    OUTPUTS:  - None.
    UPDATES:  - TobiPro::_motorSpeed.
    EFFECTS:  - None.
*/
void TobiPro::update(){
  for (int i = 0; i < NUM_MOTORS; i++){
      TobiPro::_motorSpeed[TobiPro::_motorIndices[i]] = TobiPro::calcSpeed(i); // calc speed; also updates filters
  }
}

/*      SRDELAY()
    Pauses code execution for the period corresponding to TobiPro::_dt, the inverse of your sample rate.
    INPUTS:   - None.
    OUTPUTS:  - None.
    UPDATES:  - None.
    EFFECTS:  - Suspends code execution for 1/Fs seconds (TobiPro::_dt).
*/
void TobiPro::srDelay(){
  delay(TobiPro::_dt);
}

/*      GETSPEED()
    Returns the speed of the specified motor in encoder_vals/sec.
    INPUTS:   - int motor.
    OUTPUTS:  - int motorSpeed.
    UPDATES:  - None.
    EFFECTS:  - None.
*/
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

/*      SETSAMPLERATE()
    Sets sample rate of TobiPro object.
    INPUTS:   - int Fs (sample rate, in Hz).
    OUTPUTS:  - None.
    UPDATES:  - TobiPro::_dt.
    EFFECTS:  - None.
*/

void TobiPro::setSampleRate(int Fs){
  TobiPro::_dt = 1000*(1/Fs);
}

/*      SETSPEED()
    Sets speed of a motor to a certain percentaghe of its maximum speed.
    INPUTS:   - int motor, float percent.
    OUTPUTS:  - None.
    UPDATES:  - TobiPro::_motorSpeed[motor].
    EFFECTS:  - Changes servo angular velocity.
*/
void TobiPro::setSpeed(int motor, float percent){
  int pwm = (int)(percent * 2.55);
  TobiPro::setPwm(motor, pwm);
  TobiPro::_motorSpeed[TobiPro::_motorIndices[motor]] = pwm;
}
