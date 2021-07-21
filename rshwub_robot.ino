// Include the AccelStepper library:
#include <AccelStepper.h>

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define DIR_PIN_MOTOR1 2
#define STEP_PIN_MOTOR1 3
#define DIR_PIN_MOTOR2 4
#define STEP_PIN_MOTOR2 5

#define INTERFACE_TYPE 1

AccelStepper stepper1 = AccelStepper(INTERFACE_TYPE, STEP_PIN_MOTOR1, DIR_PIN_MOTOR1);
AccelStepper stepper2 = AccelStepper(INTERFACE_TYPE, STEP_PIN_MOTOR2, DIR_PIN_MOTOR2);

void setup() {
  // Set the maximum speed in steps per second:
  stepper1.setMaxSpeed(1000);
  stepper2.setMaxSpeed(1000);
}

void loop() {
  // Set the current position to 0:
  int angle = random(-600, -100);
  int spd = random(-700, -300);

  // Reset the position to 0:
  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);

  // Run the motor backwards at 600 steps/second until the motor reaches -200 steps (1 revolution):
  while(stepper1.currentPosition() != angle)
  {
    stepper1.setSpeed(spd);
    stepper1.runSpeed();
  }
  while(stepper2.currentPosition() != angle)
  {
    stepper2.setSpeed(spd);
    stepper2.runSpeed();
  }

  delay(100);

  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);

  while(stepper1.currentPosition() != abs(angle))
  {
    stepper1.setSpeed(abs(spd));
    stepper1.runSpeed();
  }
  while(stepper2.currentPosition() != abs(angle))
  {
    stepper2.setSpeed(abs(spd));
    stepper2.runSpeed();
  }
  delay(100);

}
