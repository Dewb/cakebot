// cakebot.cpp
//
// Arduino Uno code to drive stepper on a ZMorph paste extruder
// from an ABB robot with 24V digital data lines
// using the Adafruit Motor Shield 2.3
//
// Michael Dewberry 9/30/2016

#include <Adafruit_MotorShield.h>
#include <AccelStepper.h>
#include <Bounce2.h>

#include "robotIO.h"

RobotIO robot;

// Set up the stepper driver and the AccelStepper speed control objects

Adafruit_MotorShield shield = Adafruit_MotorShield();
Adafruit_StepperMotor* pMotor = shield.getStepper(200, 1);

void forwardStepFn() { pMotor->onestep(FORWARD, SINGLE); }
void backwardStepFn() { pMotor->onestep(BACKWARD, SINGLE); }

AccelStepper stepper(forwardStepFn, backwardStepFn);

// Define pins and debouncers for the advance/retract buttons

int pinAdvanceButton = 8;
int pinRetractButton = 9;
Bounce advanceButton = Bounce();
Bounce retractButton = Bounce();

int pinControlModeSwitch = 10;

// State variables and speed defaults

enum Mode {
   Manual,
   Automatic
} controlMode;

float manualAdvanceSpeed = 400;
float manualRetractSpeed = -400;

void setup() {

   shield.begin();

   // configure input pin for the manual pluger control buttons
   pinMode(pinAdvanceButton, INPUT_PULLUP);
   advanceButton.attach(pinAdvanceButton);
   advanceButton.interval(5);

   pinMode(pinRetractButton, INPUT_PULLUP);
   retractButton.attach(pinRetractButton);
   retractButton.interval(5);

   pinMode(pinControlModeSwitch, INPUT_PULLUP);

   // start with stepper stationary
   controlMode = Manual;
   stepper.setSpeed(0);
}

void loop() {
   float stepperSpeed = 0.0;

   int modeSwitch = digitalRead(pinControlModeSwitch);
   if (modeSwitch == LOW && controlMode == Manual) {
      controlMode = Automatic;
      robot.start();
   } else if (modeSwitch == HIGH && controlMode == Automatic) {
      controlMode = Manual;
      robot.stop();
   }

   if (controlMode == Manual) {
      retractButton.update();
      advanceButton.update();
      if (retractButton.read() == LOW) {
         stepperSpeed = manualRetractSpeed;
      } else if (advanceButton.read() == LOW) {
         stepperSpeed = manualAdvanceSpeed;
      }
   } else if (controlMode == Automatic) {
      unsigned char robotSignal = robot.readByte();

      //robotSignal &= B11111100;

      if (robotSignal == 0xFF) {
         stepperSpeed = manualRetractSpeed;
      } else {
         stepperSpeed = robotSignal * 5.0;
      }
   }

   stepper.setSpeed(stepperSpeed);
   // stepper.runSpeed with speed == 0 seems to have some issues
   // in this toolchain, possibly fp exception mask?
   if (fabs(stepperSpeed) > 0.00001) {
      stepper.runSpeed();
   }
}
