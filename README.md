# SMPRobotics2017
README
Andrea Frank
7/10/2017

This library is used to control the TOBI v.3 robot. The library was developed for use by Summer
Mentorship Program, Engineering, 2017. The library provides a tobi class, with methods for 
initialization, flashing LEDs, controling the motors of each leg, and reading the encoders.

Original library and header file created by Cherag Bhagwagar (10/21/2016). Updates (denoted by $ at
the start of comments) and re-organization by Andrea Frank (7/10/2017). 

****
***** CHANGELOG: *****

By: Andrea Frank, 7/10/17	*************************************************************************************************\
Major changes: Set __pwmPin[1] to 12 instead of 5, since __encoderPin[5] = 5 a few lines down. I am
under the impression that this pin should not be written to __pwmPin[1] and then immediately after
also assigned as an input pin for __encoderPin[5], but I will check with Cherag. I also commented 
out declaration of __pcf1, __pcf2, __bit1. and __bit2 in header file, since they are declared on
their own within the .cpp library file, and do not need to be used outside.

Minor changes: Reorganization, commenting code.

\****************************************************************************************************************************
