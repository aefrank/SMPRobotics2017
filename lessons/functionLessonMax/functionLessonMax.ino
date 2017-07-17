/* Lesson: Writing functions - Max of Three Function
 *  By Andrea Frank
 *  7/17/2017
 *  SMP Robotics 2017
 *  
 *  Students are instructed to write a function that takes in three
 *  numbers from Serial input and prints the largest of the three.
*/


void setup() {
  Serial.begin(9600); // begin serial communication
  while(!Serial);     // wait for serial port to open
  Serial.setTimeout(10);  // let's you type faster without it being combined
}

void loop() {
  String inputs[3];
  // for each number
  for(int i = 0; i < 3; i++) {
    while(!Serial.available()); // wait for input
    inputs[i] = Serial.readString();    // read input
  }

  // find largest of the three using function
  float largest = findMaxOfThree(inputs); 
  // print to Serial
  Serial.println(largest);  
}


/*********************** FUNCTIONS ***********************/

/*        findMaxOfThree()    
 *    Takes an array of numbers as Strings and returns the largest
 *    as a float.
 *    INPUTS:   String numberStrings
 *    OUTPUTS:  float maxNum
 *    UPDATES:  None
*/

// takes in a String array of three numbers and outputs the largest as a float
float findMaxOfThree(String numberStrings[]){
  float nums[3];   // declare array to hold float versions of inputs

  // convert each numberString to a float and store in nums[]
  for (int i = 0; i < 3; i++){
    nums[i] = numberStrings[i].toFloat(); // get float versions of inputs
  }

  // declare variable to hold largest value, start with first input
  float maxNum = nums[0]; 

  // for each input, check if bigger than current maxNum and, if so, reassign maxNum to that value
  for(int i = 1; i < 3; i++){  // start from i = 1, not i = 0, since we know maxNum == nums[0] at this point!
    // if nums[i] is bigger than maxNum, then maxNum should equal num[i]
    if(maxNum < nums[i]){
      maxNum = nums[i]; 
    }
  }
  return maxNum;
}


