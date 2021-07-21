#include <AccelStepper.h>

#define INTERFACE_TYPE 1
#define NUM_MOTORS 2
#define NUM_ROUTINES 3

// Robot head
#define MOTOR1 0
#define DIR_PIN_MOTOR1 2
#define STEP_PIN_MOTOR1 3

// Robot body
#define MOTOR2 1
#define DIR_PIN_MOTOR2 4
#define STEP_PIN_MOTOR2 5

// Define motors
AccelStepper stepper[NUM_MOTORS];

// Array of different routine functions
void (*routines[NUM_ROUTINES])();



/** 
/  ----- Helper Functions -----
**/

// Moves specifed motor to angle with given speed
void move_motor_to_angle(int16_t angle, int16_t spd, uint8_t motor_num) {
  while(stepper[motor_num].currentPosition() != angle)
  {
    stepper[motor_num].setSpeed(spd);
    stepper[motor_num].runSpeed();
  }
}

// Moves motor1 to angle1 and motor2 to angle 2 at the same time
// This function is gross but is required for moving both motors at once
void move_motors_to_angle(int16_t angle1, int16_t spd1, int16_t angle2, int16_t spd2) {
  bool done = false;
  while(!done)
  {
    done = true;
    if(stepper[MOTOR1].currentPosition() != angle1){
      stepper[MOTOR1].setSpeed(spd1);
      stepper[MOTOR1].runSpeed();
      done = false;
    }
    if(stepper[MOTOR2].currentPosition() != angle2){
      stepper[MOTOR2].setSpeed(spd2);
      stepper[MOTOR2].runSpeed();
      done = false;
    }
  }
}

// Reset motor position to 0
void reset_motor(uint8_t motor_num) {
  stepper[MOTOR1].setCurrentPosition(0);
}

// Reset all motors positions to 0
void reset_motors() {
  for(uint8_t i = 0; i < NUM_MOTORS; i++) {
    stepper[i].setCurrentPosition(0);
  }
}



/** 
/  ----- Routines -----
/  Routines for the robot to do. When adding define function here. Initialize in setup(). Increment NUM_ROUTINES
**/

void move_head_around() {
  reset_motors();
  int spd = random(-700, -300);
  move_motor_to_angle(-3000, spd, MOTOR1);
  delay(200);
  reset_motors();

  spd *= -1;
  move_motor_to_angle(3000, spd, MOTOR1);
  delay(200);
  reset_motors();
}

void one_at_a_time() {
  int angle = random(-600, -100);
  int spd = random(-700, -300);

  reset_motors();
  
  move_motor_to_angle(angle, spd, MOTOR1);
  move_motor_to_angle(angle, spd, MOTOR2);
  delay(100);
  reset_motors();

  angle *= -1;
  spd *= -1;
  move_motor_to_angle(angle, spd, MOTOR1);
  move_motor_to_angle(angle, spd, MOTOR2);
  delay(100);
  reset_motors();
}

void both_baby() {
  int angle = random(-600, -100);
  int spd = random(-700, -300);
  
  reset_motors();

  move_motors_to_angle(angle, spd, angle, spd);
  delay(100);
  reset_motors();

  angle *= -1;
  spd *= -1;
  move_motors_to_angle(angle, spd, angle, spd);
  delay(100);
  reset_motors();
}



/** 
/  ----- Core setup and loop -----
**/

void setup() {
  // Initialize routines
  routines[0] = move_head_around;
  routines[1] = one_at_a_time;
  routines[2] = both_baby;
  
  // Set up motors
  stepper[MOTOR1] = AccelStepper(INTERFACE_TYPE, STEP_PIN_MOTOR1, DIR_PIN_MOTOR1);
  stepper[MOTOR2] = AccelStepper(INTERFACE_TYPE, STEP_PIN_MOTOR2, DIR_PIN_MOTOR2);
  
  // Set the maximum speed in steps per second:
  for(uint8_t i = 0; i < NUM_MOTORS; i++) {
    stepper[i].setMaxSpeed(1000);
  }
}

void loop() {
  // Select routine
  int routine_num = random(0, NUM_ROUTINES);

  // Call routine
  routines[routine_num]();

  // Time between routines
  delay(2000);
}
