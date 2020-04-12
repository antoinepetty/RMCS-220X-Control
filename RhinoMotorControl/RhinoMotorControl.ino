#include <Wire.h>
#include "src/RMCS-220X.h"

#define ADDR 0x08 // Address of motor on i2c bus

RMCS220X motor = RMCS220X(ADDR);

void setup() {
  Serial.begin(9600);
  Serial.println("Start program");

  motor = RMCS220X(ADDR);

  printDebugInfo();
  
  Serial.println("Setting position to 0 deg");
  motor.goToPositionInDegrees(0);
  delay(5000);
  Serial.println("Position is " + String(motor.readEncoderPositionInDegrees()));

  Serial.println("Setting position to 180 deg");
  motor.goToPositionInDegrees(180);
  delay(5000);
  Serial.println("Position is " + String(motor.readEncoderPositionInDegrees()));

  Serial.println("Setting position to 0 deg");
  motor.goToPositionInDegrees(0);
  delay(5000);
  Serial.println("Position is " + String(motor.readEncoderPositionInDegrees()));

  Serial.println("Setting position to -180 deg");
  motor.goToPositionInDegrees(180);
  delay(5000);
  Serial.println("Position is " + String(motor.readEncoderPositionInDegrees()));
  
  Serial.println("End of test.");
}

void loop() {
  
}

void printDebugInfo(){
  Serial.println("Max motor speed is "+String(motor.readMaxSpeed()));
  Serial.println("Current motor speed is "+String(motor.readSpeed()));
  Serial.println("Speed damping is "+String(motor.readSpeedDamping()));
  Serial.println("Encoder Position is "+String(motor.readEncoderPositionInDegrees()));
  Serial.println("Go-to position is "+String(motor.readGoToPositionInDegrees()));
  Serial.println("Speed-feedback gain term is "+String(motor.readSpeedFeedbackGainTerm()));
  Serial.println("P-gain term is "+String(motor.readPGainTerm()));
  Serial.println("I-gain term is "+String(motor.readIGainTerm()));
}
