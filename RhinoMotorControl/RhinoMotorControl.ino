#include <Wire.h>
#include "src/RMCS-220X.h"

//#define ADDR 0x08 // Address of motor on i2c bus

void setup() {
  Serial.begin(9600);
  Serial.println("Starting i2c connection...");
  //Wire.begin(); // join i2c bus

  RMCS220X motor = RMCS220X(0x08);



  
  Serial.println("Setting position to 0 deg");
  motor.goToPositionInSteps(0);
  delay(5000);
  Serial.println("Position is " + String(motor.readEncoderPositionInSteps()));

  Serial.println("Setting position to 180 deg");
  motor.goToPositionInSteps(5);
  delay(5000);
  Serial.println("Position is " + String(motor.readEncoderPositionInSteps()));

  Serial.println("Setting position to 0 deg");
  motor.goToPositionInSteps(0);
  delay(5000);
  Serial.println("Position is " + String(motor.readEncoderPositionInSteps()));

  Serial.println("Setting position to -180 deg");
  motor.goToPositionInSteps(5);
  delay(5000);
  Serial.println("Position is " + String(motor.readEncoderPositionInSteps()));
  
  Serial.println("End of test.");
}

void loop() {
  
}

/*void printDebugInfo(){
  Serial.println("Max motor speed is "+String(readMaxSpeed()));
  Serial.println("Current motor speed is "+String(readMotorSpeed()));
  Serial.println("Speed damping is "+String(readSpeedDamping()));
  Serial.println("Encoder Position is "+String(readEncoderPosition()));
  Serial.println("Go-to position is "+String(readGoToPosition()));
  Serial.println("Speed-feedback gain term is "+String(readSpeedFeedbackGainTerm()));
  Serial.println("P-gain term is "+String(readPGainTerm()));
  Serial.println("I-gain term is "+String(readIGainTerm()));
}*/
