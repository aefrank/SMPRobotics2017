/* Lesson: Writing functions - Power Function
 *  By Andrea Frank
 *  7/17/2017
 *  SMP Robotics 2017
 *  
 *  Students are first instructed to write a function that takes in a base
 *  and an exponent and returns the base raised to the exponent. Students
 *  check their function by checking if power(10,3) == 1000, printed to the
 *  Serial monitor. 
 *  Students are then taught Serial inputs, and requested to write a program
 *  that reads two numbers from the Serial input (first number, enter, second
 *  number, enter, then calculate) and print the first raised to the second
 *  back to the Serial monitor.
 *  
*/

void setup() {
  Serial.begin(9600); // begin serial communication
  while(!Serial);     // wait for serial port to open
  Serial.setTimeout(10);  // let's you type faster without it being combined
}

void loop() {
  float nums[2];

  // for each number
  for(int i = 0; i < 2; i++){
    // wait for number to be sent; do nothing until available
    while(!Serial.available());
    
    // if available, read String
    String str = Serial.readString();
    
    // convert to float (chose float over int for capacity for higher numbers)
    nums[i] = str.toFloat();
  }

  // calculate exponent
  float ans = power(nums[0], nums[1]);
  
  // print to Serial monitor
  Serial.println("Answer: " + ans);
}



/*********************** FUNCTIONS ***********************/

/*        POWER()     <int version>
 *    Calculates a base raised to a power through repeated multiplication. 
 *    Can only take integer exponents >= 0. Treats negatives as 0.
 *    INPUTS:   int base, int exponent
 *    OUTPUTS:  int answer
 *    UPDATES:  None
*/
int power(int base, int exponent){
  // edge case: if exponent = 0, answer = 1
  int answer = 1;
  for (int i = 0; i < exponent; i++){
    answer *= base;   // multiply by base exponent times (power = repeated multiplication)
  }
  return answer;
}

/*        POWER()   <float version>
 *    Calculates a base raised to a power through repeated multiplication. 
 *    Can only take integer exponents >= 0. Treats negatives as 0.
 *    INPUTS:   float base, int exponent
 *    OUTPUTS:  float answer
 *    UPDATES:  None
*/
float power(float bae, int exponent){
  // edge case: if exponent = 0, answer = 1
  float answer = 1;
  for (int i = 0; i < exponent; i++){
    answer *= base;   // multiply by base exponent times (power = repeated multiplication)
  }
  return answer;
}
