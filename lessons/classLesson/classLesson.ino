/* Lesson: Writing classes - Person class
 *  By Andrea Frank
 *  7/17/2017
 *  SMP Robotics 2017
 *  
 *  Students are first instructed to write a class called Person that 
 *  can be instantiated as individual Persons. They are requested to
 *  give the Person class public fields for name and occupation, and
 *  private fields for birthdate (day, month, year). They are not
 *  allowed to have an age field. Students should write a public method
 *  to introduce the Person object's name, age, and occupation; and a
 *  private method to calculate their age from their (private) birth-
 *  date. This will be a helper function called by the public 
 *  introduce() function.
 *  
 *  Students must then write a program to test their class. The loop()
 *  should end with while(1); to keep the program from looping.
 *  
 *  Bonus: Write a program where you can input a person’s information
 *  from the Serial monitor! (You can get rid of while(1); here so
 *  the program can accept new information immediately after each
 *  introduction.)
*/

#include "Person.h"

/*********************** GLOBAL VARIABLES ***********************/

//Person person;  // declare instance of Person object;
                // note: declared globally so can be accessed by both 
                    // setup() and loop()!
       // commented out because it only needs to be accessed in loop()
          // for bonus program, can be redeclared each loop


/************************* MAIN PROGRAM *************************/

// setup Serial communication
void setup() {
  // Serial setup
  Serial.begin(9600); // begin serial communication
  while(!Serial);     // wait for serial port to open
  Serial.setTimeout(10);  // let's you type faster without Strings being combined

  // construct Person object
  // person = Person("Andi", "SMP Coordinator", 15, 4, 1995);   // for non-Serial version
  
}

// gather Serial inputs, construct Person object, and introduce
void loop() {
  // gather Strings from command line
  String str[5];  // 5 pieces of info necessary: name, job, birthday, birth month, birth year
  for(int i = 0; i < 5; i++){
    while(!Serial.available()); // wait for each string
    str[i] = Serial.readString();
  }

  int bdate[3];
  for(int i = 0; i < 3; i++){
    bdate[i] = str[i+2].toInt();  // turn birthdate info into ints
  }

  // create Person object with information from Serial
  Person person = Person(str[0], str[1], bdate[0], bdate[1], bdate[2]);

  // introduce person
  person.introduce();
  
} // loop and wait for more inputs
