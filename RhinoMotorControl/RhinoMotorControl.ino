#include <Wire.h>

#define ADDR 0x08 // Address of motor on i2c bus

#define MAX_SPEED_ATTR 0
#define SPEED_ATTR 1
#define SPEED_DAMP_ATTR 2
#define ENCODER_POS_ATTR 3
#define GO_TO_POS_ATTR 4
#define SPEED_FDBK_GAIN_TERM_ATTR 5
#define P_GAIN_TERM_ATTR 6
#define I_GAIN_TERM_ATTR 7
#define RELATIVE_GO_TO_ATTR 8
#define DEGREES_RESOLUTION 0.2

void setup() {
  Serial.begin(9600);
  Serial.println("Starting i2c connection...");
  Wire.begin(); // join i2c bus

  Serial.println("Setting position to 0");
  setEncoderPositionInDegrees(0);
  delay(2000);
  Serial.println("Position is " + String(getEncoderPosition()));

  Serial.println("Setting position to 180");
  setEncoderPositionInDegrees(180);
  delay(2000);
  Serial.println("Position is " + String(getEncoderPosition()));

  Serial.println("Setting position to 0");
  setEncoderPositionInDegrees(0);
  delay(2000);
  Serial.println("Position is " + String(getEncoderPosition()));

  Serial.println("Setting position to -180");
  setEncoderPositionInDegrees(-180);
  delay(2000);
  Serial.println("Position is " + String(getEncoderPosition()));
  
  
  Serial.println("End of test.");
}

void loop() {
  
}

/* Set the speed of the motor (-255 to 255) */
void setMotorSpeed(int motorSpeed){
  set2ByteAttr(SPEED_ATTR, motorSpeed);
}

/* Get the speed of the motor (-255 to 255) */
int getMotorSpeed(){
  return get2ByteAttr(SPEED_ATTR);
}

/* Set the maximum speed of the motor (0 to 255) */
void setMaxSpeed(int maxSpeed){
  set2ByteAttr(MAX_SPEED_ATTR, maxSpeed);
}

/* Get the maximum speed of the motor (0 to 255) */
int getMaxSpeed(){
  return get2ByteAttr(MAX_SPEED_ATTR);
}

/* Set the speed damping (0 to 255) */
void setSpeedDamping(int value){
  set2ByteAttr(SPEED_DAMP_ATTR, value);
}

/* Get the speed damping (0 to 255) */
int getSpeedDamping(){
  return get2ByteAttr(SPEED_DAMP_ATTR);
}

/* Set the speed feedback gain term (0 to 32767) */
void setSpeedFeedbackGainTerm(int value){
  set2ByteAttr(SPEED_FDBK_GAIN_TERM_ATTR, value);
}

/* Get the speed feedback gain term (0 to 32767) */
int getSpeedFeedbackGainTerm(){
  return get2ByteAttr(SPEED_FDBK_GAIN_TERM_ATTR);
}

/* Set the p-gain term (0 to 32767) */
void setPGainTerm(int value){
  set2ByteAttr(P_GAIN_TERM_ATTR, value);
}

/* Get the p-gain term (0 to 32767) */
int getPGainTerm(){
  return get2ByteAttr(P_GAIN_TERM_ATTR);
}

/* Set the i-gain term (0 to 32767) */
void setIGainTerm(int value){
  set2ByteAttr(I_GAIN_TERM_ATTR, value);
}

/* Get the i-gain term (0 to 32767) */
int getIGainTerm(){
  return get2ByteAttr(I_GAIN_TERM_ATTR);
}

/* Set the encoder position (-2147483647 to 2147483647) */
void setEncoderPosition(long value){
  set4ByteAttr(ENCODER_POS_ATTR, value);
}

/* Get the encoder position (-2147483647 to 2147483647) */
int getEncoderPosition(){
  return get4ByteAttr(ENCODER_POS_ATTR);
}

/* Set the "go to" position (-2147483647 to 2147483647) */
void goToPosition(long value){
  set4ByteAttr(GO_TO_POS_ATTR, value);
}

/* Get the "go to" position (-2147483647 to 2147483647) */
int getGoToPosition(){
  return get4ByteAttr(GO_TO_POS_ATTR);
}

/* Set the relative "go to" position (-2147483647 to 2147483647) */
void goToRelativePosition(long value){
  set4ByteAttr(RELATIVE_GO_TO_ATTR, value);
}



/* Set the encoder position in degrees */
void setEncoderPositionInDegrees(float valueInDegrees){
  set4ByteAttr(ENCODER_POS_ATTR, stepsFromDegrees(valueInDegrees));
}

long stepsFromDegrees(float angle){
  return angle/DEGREES_RESOLUTION;
}

/* Sets any 2 byte attribute */
void set2ByteAttr(byte command, int value){
  Wire.beginTransmission(ADDR);
  Wire.write(byte(command));          // sends command byte
  Wire.write(byte(lowByte(value)));   // sends value byte lsb
  Wire.write(byte(highByte(value)));  // sends value byte msb
  Wire.endTransmission();
}

/* Sets any 4 byte attribute */
void set4ByteAttr(byte command, long value){
  Wire.beginTransmission(ADDR);
  Wire.write(byte(command));      // sends command byte
  Wire.write((byte) value);       // sends value byte lsb
  Serial.println("Sent byte: "+String((byte) value));
  Wire.write((byte) value >> 8);
  Serial.println("Sent byte: "+String((byte) value >> 8));
  Wire.write((byte) value >> 16);
  Serial.println("Sent byte: "+String((byte) value >> 16));
  Wire.write((byte) value >> 24); // sends value byte msb
  Serial.println("Sent byte: "+String((byte) value >> 24));
  Wire.endTransmission();
}

/* Gets any 2 byte attribute */
int get2ByteAttr(byte command){
  return (int) getAttr(command, 2);
}

/* Gets any 4 byte attribute */
long get4ByteAttr(byte command){
  return getAttr(command, 4);
}

/* Get the value of any attribute */
long getAttr(byte command,int numberOfBytes){
  long result = 0;
  Wire.beginTransmission(ADDR);
  Wire.write(byte(command));          // sends command byte
  Wire.endTransmission();
  delay(5); // Delay to allow the motor's controller to react to the previous message
  Wire.requestFrom(ADDR, numberOfBytes);
  //while(numberOfBytes > Wire.available()){  } // Wait for enough bytes
  if (numberOfBytes <= Wire.available()) { // if correct num of bytes received
    for(int i=0; i<numberOfBytes; i++){
      long currentByte = Wire.read();
      currentByte = currentByte << (8*i);
      result |= currentByte;
    }
  }
  return result;
}
