# SMPRobotics2017
README
Andrea Frank
Created 7/10/2017

This respository contains pertinent code for Summer Mentorship Program, Engineering, 2017.
This includes the library used to control the TOBI v.3 robot, as well as instructional
programs used to teach coding concepts. The Tobi.h library provides a tobi class, with
methods for initialization, flashing LEDs, controling the motors of each leg, and reading
the encoders.

Original library and header file created by Cherag Bhagwagar (10/21/2016). Updates (denoted by $ at
the start of comments) and re-organization by Andrea Frank (see changelog). 

****
## ***** CHANGELOG: *****

<b>By: Andrea Frank, 7/24/17</b>	*************************************************************************************************\
<i>Major changes:</i> Changed `getAngle()` to `readEncoders()`, since that's really what you do. `analogUpdate()` is now private (renamed `_analogUpdate()`) and called automatically when calling `readEncoders()`. Added a `calibrateEncoders()` method, because sometimes the max encoder value varies. Took out `#include <TimerOne.h>` since we don't end up using it. 

<i>Minor Changes:</i> Cleaned up library comments and such in general. 

<b>By: Andrea Frank, 7/17/17</b>	*************************************************************************************************\
<i>Major changes:</i> Uploaded example files from programming lessons to repository.

<i>Minor Changes:</i> Updated README.md

<b>By: Andrea Frank, 7/12/17</b>	*************************************************************************************************\
<i>Major changes:</i> Changed `tobi` class to `Tobi` to keep with class naming convention. I didn't
want to confuse the students by using lowercase for a class after teaching them that it's convention
to use uppercase. Also uploaded keywords.txt (also included in tobi_7-12-17.ZIP) so Arduino will
recognize class and method names from Tobi library.

<b>By: Andrea Frank, 7/10/17</b>	*************************************************************************************************\
<i>Major changes:</i> Set `__pwmPins[1]` back to 5. Although both `__pwmPins[1]` and `__encoderPins[5]`
are equal to 5, they are mapped to two separate pins (digital pin 5 and analog pin 5, respectively)
when called for IO.

<b>By: Andrea Frank, 7/10/17</b>	*************************************************************************************************\
<i>Major changes:</i> Set `__pwmPin[1]` to 12 instead of 5, since `__encoderPin[5]` = 5 a few lines down. I am
under the impression that this pin should not be written to `__pwmPin[1]` and then immediately after
also assigned as an input pin for `__encoderPin[5]`, but I will check with Cherag. I also commented 
out declaration of `__pcf1`, `__pcf2`, `__bit1`, and `__bit2` in header file, since they are declared on
their own within the .cpp library file, and do not need to be used outside.

<i>Minor changes:</i> Reorganization, commenting code.

\*************************************************************************************************
