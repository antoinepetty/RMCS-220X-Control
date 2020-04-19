#include <Wire.h>
#include "src/RMCS-220X.h"

/* Configure connected motors */
#define NUMBER_OF_MOTORS 2
int motorAddress[NUMBER_OF_MOTORS] = {0x01,0x06};
#define MAX_ATTEMPTS 10 // Number of attempts to turn before printign debug info
#define MARGIN_OF_ERROR 1 // How many degrees margin of error when checking current position

/* Array of all connected motors */
RMCS220X motor[NUMBER_OF_MOTORS];

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUMBER_OF_MOTORS; i++) {
    Serial.print("Connecting to motor " + String(i) + " at address 0x");
    Serial.println(motorAddress[i], HEX);
    motor[i].begin(motorAddress[i]);
  }
  // Max Speed
  Serial.print("Motor 0 Max Speed:");
  Serial.println(motor[0].readMaxSpeed());
  Serial.print("Motor 1 Max Speed:");
  Serial.println(motor[1].readMaxSpeed());
}

void loop() {
  Serial.println("\nNext Loop");

  // Read Position
  Serial.print("Motor 0 Position:");
  Serial.println(motor[0].readEncoderPositionInDegrees());
  Serial.print("Motor 1 Position:");
  Serial.println(motor[1].readEncoderPositionInDegrees());
  
  // Go to 0
  Serial.println("Going to 0 deg");
  motor[0].goToPositionInDegrees(0);
  motor[1].goToPositionInDegrees(0);
  waitForMotorPositionDegrees(0,0);
  waitForMotorPositionDegrees(1,0);

  // Read Position
  Serial.print("Motor 0 Position:");
  Serial.println(motor[0].readEncoderPositionInDegrees());
  Serial.print("Motor 1 Position:");
  Serial.println(motor[1].readEncoderPositionInDegrees());

  // Go to 180
  Serial.println("Going to 180 deg");
  motor[0].goToPositionInDegrees(180);
  motor[1].goToPositionInDegrees(180);
  waitForMotorPositionDegrees(0,180);
  waitForMotorPositionDegrees(1,180);

  // Read Position
  Serial.print("Motor 0 Position:");
  Serial.println(motor[0].readEncoderPositionInDegrees());
  Serial.print("Motor 1 Position:");
  Serial.println(motor[1].readEncoderPositionInDegrees());
}

void waitForMotorPositionDegrees(int motorNum, double degreesPos){
  Serial.print("Waiting for motor to move");
  int attempts = 0;
  double actualPosition = motor[motorNum].readEncoderPositionInDegrees();
  while(actualPosition > degreesPos+MARGIN_OF_ERROR || actualPosition < degreesPos-MARGIN_OF_ERROR){
    if (attempts == MAX_ATTEMPTS){
      attempts = 0;
      Serial.println("Intended position: " + String(degreesPos) + " Current position: " + String(actualPosition));
    }
    else{
      Serial.print(".");
    }
    delay(500);
    double previousPosition = actualPosition;
    actualPosition = motor[motorNum].readEncoderPositionInDegrees();
    if(previousPosition == actualPosition){
      Serial.println("Motor not moving, trying command again.");
      motor[motorNum].goToPositionInDegrees(degreesPos);
    }
    attempts++;
  }
  Serial.println("done!");
}
