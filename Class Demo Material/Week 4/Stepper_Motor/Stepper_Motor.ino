#include <Stepper.h>

// change this to the number of steps on your motor
int STEPS = 32;

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 8, 9, 10, 11);
int pot = A0;

void setup() {
  Serial.begin(9600);
  pinMode(pot, INPUT);
}

void loop() {
  // get the sensor value
  int potReading = analogRead(pot);
  int motorDirection;
  if(potReading >= 512){
    motorDirection = -64;
  }else{
    motorDirection = 64;
  }
  Serial.println(motorDirection);

  //define the motor speed between 100 and 700 depending on the state of the potentiometer:
  int motorSpeed = abs(map(potReading, 0, 1023, -600, 600));
  motorSpeed = motorSpeed + 100;

  //move the stepper:
  stepper.setSpeed(motorSpeed);
  stepper.step(motorDirection);
  //delay(1000);
  
}
