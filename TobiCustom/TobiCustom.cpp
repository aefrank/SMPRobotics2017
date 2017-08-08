
#include <TobiCustom.h>

#define WHEEL0 0
#define WHEEL1 1

TobiCustom::TobiCustom(){

}

/*          DRIVEFWD()  
    Sets pwm of wheel motors to drive forward at same speed, so TOBI bot moves 
    directly forward. Speed is input in percentage of max speed.
    INPUTS:   - int percentSpeed
    OUTPUTS:  - None.
    UPDATES:  - _pwmPin[0] and _pwmPin[1]
    EFFECTS:  - Drives TOBI forward.
*/
void TobiCustom::driveFwd(int percentSpeed){
  int spd = percentSpeed * 255 / 100; // calculate percentage on 0-255 scale
  TobiCustom::setPwm(WHEEL0, spd);
  TobiCustom::setPwm(WHEEL1, spd);

}