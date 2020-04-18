#include <Wire.h>
#include <RMCS-220X.h>

/* Configure connected motors */
#define NUMBER_OF_MOTORS 2
int motorAddress[NUMBER_OF_MOTORS] = {0x15,0x16};

/* Array of all connected motors */
RMCS220X motor[NUMBER_OF_MOTORS];

RMCS220X motor;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUMBER_OF_MOTORS; i++) {
    Serial.print("Connecting to motor " + String(i) + " at address 0x");
    Serial.println(motorAddress[i], HEX);
    motor[i].begin(motorAddress[i]);
  }
}

void loop() {
  motor[0].goToPositionInDegrees(0);
  motor[1].goToPositionInDegrees(0);
  waitForMotorPositionDegrees(0,0);
  waitForMotorPositionDegrees(1,0);

  motor[0].goToPositionInDegrees(-180);
  motor[1].goToPositionInDegrees(180);
  waitForMotorPositionDegrees(0,-180);
  waitForMotorPositionDegrees(1,180);
}

void waitForMotorPositionDegrees(int motorNum, double degreesPos){
  while(motor[motorNum].readEncoderPositionInDegrees() != degreesPos){
    delay(50);
  }
}
