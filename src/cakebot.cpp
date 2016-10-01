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

// Set up the stepper driver and the AccelStepper speed control objects

Adafruit_StepperMotor motor;

void forwardStepFn() { motor.onestep(FORWARD, SINGLE); }
void backwardStepFn() { motor.onestep(BACKWARD, SINGLE); }

AccelStepper stepper(forwardStepFn, backwardStepFn);

// Define pins and debounce object for the retract button

int pinRetractButton = 8;
Bounce retractButton = Bounce();

// Define state variables for speed control

float stepperSpeed;
float retractSpeed = -200;

void setup() {
   // configure pins for reading 8 channels from ABB digital output
   initializeRobotPins();

   // configure input pin for the plunger retract button
   pinMode(pinRetractButton, INPUT_PULLUP);
   retractButton.attach(pinRetractButton);
   retractButton.interval(5);

   // start with stepper stationary
   stepper.setSpeed(0);
}

void loop() {
   int robotSignal = readRobotSignal();

   retractButton.update();
   if (retractButton.read()) {
      stepperSpeed = retractSpeed;
   } else {
      stepperSpeed = (float)robotSignal;
   }

   stepper.setSpeed(stepperSpeed);
   stepper.runSpeed();
}
