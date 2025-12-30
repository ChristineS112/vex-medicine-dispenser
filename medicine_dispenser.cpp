#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>




#include "vex.h"


using namespace vex;


// Brain should be defined by default
brain Brain;




// START IQ MACROS
#define waitUntil(condition)                                                   
  do {                                                                         
    wait(5, msec);                                                             
  } while (!(condition))


#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END IQ MACROS




// Robot configuration code.
inertial BrainInertial = inertial();
motor MotorTilt = motor(PORT1, true);
motor MotorDispense = motor(PORT2, false);
touchled TouchLED7 = touchled(PORT7);
bumper Bumper5 = bumper(PORT5);
motor MotorDrawer = motor(PORT3, true);
distance Distance6 = distance(PORT6);




// generating and setting random seed
void initializeRandomSeed(){
  wait(100,msec);
  double xAxis = BrainInertial.acceleration(xaxis) * 1000;
  double yAxis = BrainInertial.acceleration(yaxis) * 1000;
  double zAxis = BrainInertial.acceleration(zaxis) * 1000;
  // Combine these values into a single integer
  int seed = int(
    xAxis + yAxis + zAxis
  );
  // Set the seed
  srand(seed);
}






void vexcodeInit() {


  // Initializing random seed.
  initializeRandomSeed();
}


#pragma endregion VEXcode Generated Robot Configuration


// Include the IQ Library
#include "iq_cpp.h"


// Allows for easier use of the VEX Library
using namespace vex;


//function prototypes


void configureAllSensors();
void waitForTouchLED();
int setAlarm();
void waitForBumper();
void playAlarm();
void alertRefill();
void dispense();
void drawer(int direction);
bool generateReport (int countTouchSensor);
void printReport (bool missedTimes, int numMissedTimes);




void configureAllSensors(){
  BrainInertial.calibrate();
  wait(2,seconds);
  BrainInertial.setHeading(0,degrees);
  BrainInertial.setRotation(0,degrees);
  MotorTilt.setPosition(0,turns);
  MotorDispense.setPosition(0,turns);
  MotorDrawer.setPosition(0,turns);
  Brain.Screen.clearScreen();
  Brain.Screen.setFont(mono15);
}


int setAlarm() {
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Press bumper");
  Brain.Screen.newLine();
  Brain.Screen.print("to set alarm");
  Brain.Screen.newLine();
  waitForBumper();
  int num_hours = 0;
 
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Number of hours: %d", num_hours);
  wait(0.5, seconds);


  while(!TouchLED7.pressing())
  {
    if(Bumper5.pressing())
    {
      wait(15, msec);
      Brain.Screen.setCursor(1,1);
      num_hours++;
      Brain.Screen.clearScreen();
      Brain.Screen.print("Number of hours: %d", num_hours);
      wait(0.5, seconds);
    }
  }
  int num_minutes = 0;
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
 
  while(TouchLED7.pressing())
  {}


  while(!TouchLED7.pressing())
  {
     
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("Minutes: %d", num_minutes);
    if(Bumper5.pressing())
    {
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1,1);
      num_minutes+= 1;
      Brain.Screen.print("Minutes: %d", num_minutes);
      wait(0.3, seconds);
    }
  }
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Press TouchLED to ");
  Brain.Screen.newLine();
  Brain.Screen.print("set alarm for ");
  Brain.Screen.newLine();
  Brain.Screen.print("%d hrs, %d min", num_hours, num_minutes);
  wait(1, seconds);
  waitForTouchLED();


  /*
  1 minute = 1 second
  1 hour = 5 seconds
  */
  int time_set_in_mins = num_hours*5 + num_minutes;
  return time_set_in_mins;
}


void waitForBumper() {
    while(!Bumper5.pressing())
    {}
    while(Bumper5.pressing())
    {}
}


void waitForTouchLED() {
    while(!TouchLED7.pressing())
    {}
    while(TouchLED7.pressing())
    {}
}


void playAlarm()
{
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("1. Dispense medicine: ");
  Brain.Screen.newLine();
  Brain.Screen.print("press Touch Sensor");
  Brain.Screen.newLine();
  Brain.Screen.print("2. Skip medicine: ");
  Brain.Screen.newLine();
  Brain.Screen.print("press bumper");
  Brain.Screen.newLine();


  Brain.playNote(4, 4, 250);
  Brain.playNote(4, 4, 250);
  Brain.playNote(4, 2, 250);
  Brain.playNote(4, 0, 250);
  Brain.playNote(4, 3, 250);
  Brain.playNote(4, 2, 250);
  Brain.playNote(4, 2, 500);
  Brain.playNote(4, 0, 250);
  Brain.playNote(4, 2, 250);
  Brain.playNote(4, 3, 250);
  Brain.playNote(4, 2, 250);
  Brain.playNote(4, 0, 500);
  wait(0.5, seconds);
}


void alertRefill()
{
 
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Time to refill dispenser");
  Brain.Screen.newLine();
  Brain.Screen.print("Do not forget to put screen back");
  Brain.Screen.newLine();
  Brain.Screen.print("to prevent pills from spilling");
  MotorTilt.spin(forward, 20, pct);
  while (MotorTilt.position(degrees) < 70)
  {}
  MotorTilt.stop();
 
  Brain.playNote(4, 0, 250);
  Brain.playNote(4, 2, 250);
  Brain.playNote(4, 4, 250);
  Brain.playNote(4, 0, 250);
  Brain.playNote(3, 5, 250);
  Brain.playNote(3, 6, 250);
  Brain.playNote(4, 0, 500);


  Brain.playNote(3, 5, 250);
  Brain.playNote(3, 5, 250);
  Brain.playNote(4, 2, 250);
  Brain.playNote(4, 4, 250);
  Brain.playNote(4, 0, 500);
}


void dispense()
{
  MotorDispense.spin(forward, 10, percent);
  while(MotorDispense.position(degrees) < 23)
  {}
  MotorDispense.stop(brake);
  MotorDispense.setPosition(0, degrees);
  wait(0.5,seconds);
}


void drawer(int direction)
{
  if (direction == 0) // Extend
  {
    MotorDrawer.spin(forward, 25, pct);
    while (MotorDrawer.position(degrees) < 45)
    {}
    MotorDrawer.stop();
    MotorDrawer.setPosition(0, degrees);
  }
  else if (direction == 1) // Retract
  {
    MotorDrawer.spin(reverse, 25, pct);
    while (MotorDrawer.position(degrees) > -45)
    {}
    MotorDrawer.stop();
    MotorDrawer.setPosition(0, degrees);
  }
}


bool generateReport (int countTouchSensor)
{
    bool hasSkipped = false;
    if ( countTouchSensor >= 1)
    {
        hasSkipped = true;
    }
    return hasSkipped;
}


void printReport (bool missedTimes, int numMissedTimes)
{
  if (missedTimes == false)
  {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("You missed none");
    Brain.Screen.newLine();
    Brain.Screen.print("of the medication!");
    Brain.Screen.newLine();
  }
  else if (missedTimes == true)
  {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("You have missed");
    Brain.Screen.newLine();
    Brain.Screen.print("medication %d times", numMissedTimes);
  }
}




int main()
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  configureAllSensors();
  // Repeat until dispenser is empty


  int skipCounter = 0;
  int time = setAlarm();
  Brain.Timer.reset();
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Timer has");
  Brain.Screen.newLine();
  Brain.Screen.print("been set!");


  // Set as 5 for the purpose of the demo
  for(int i = 0; i < 3; i++)
  {
    while(Brain.Timer.value() < time)
    {}
    playAlarm(); // Already has if bumper pressing then jingle stops


    while(!Bumper5.pressing() && !TouchLED7.pressing())
    {}
    bool skipping = false;
    if (Bumper5.pressing())
    {
      skipCounter += 1;      
      skipping = true;
    }  
    else if (TouchLED7.pressing())
    {
      dispense();
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print("Medicine dispensed!");
      drawer(0);
    }
   
    bool hasSkipped = generateReport(skipCounter);
    printReport(hasSkipped, skipCounter);
    waitForTouchLED();
    wait(1, msec); // apply wait time so the text erases properly
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    time = setAlarm();


    Brain.Timer.reset();
    Brain.Screen.clearScreen();
    Brain.Screen.newLine();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("Timer has");
    Brain.Screen.newLine();
    Brain.Screen.print("been set!");
   
    if(!skipping)
    {
      float approx_dist = 30.0;
      wait(20, msec);
      while(Distance6.objectDistance(inches) < approx_dist)
      {}
      drawer(1);
    }
  }


  alertRefill();  
  Brain.programStop();
  return EXIT_SUCCESS;
}
