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

  // Calibrate motor. Set current position as 0
  setEncoderPosition(0);

  printDebugInfo();

  
  Serial.println("Setting position to 0 deg");
  goToPosition(stepsFromDegrees(0))
  delay(5000);
  Serial.println("Position is " + String(getEncoderPosition()));

  Serial.println("Setting position to 180 deg");
  goToPosition(stepsFromDegrees(180))
  delay(5000);
  Serial.println("Position is " + String(getEncoderPosition()));

  Serial.println("Setting position to 0 deg");
  goToPosition(stepsFromDegrees(0))
  delay(5000);
  Serial.println("Position is " + String(getEncoderPosition()));

  Serial.println("Setting position to -180 deg");
  goToPosition(stepsFromDegrees(-180))
  delay(5000);
  Serial.println("Position is " + String(getEncoderPosition()));
  
  Serial.println("End of test.");
}

void loop() {
  
}

void printDebugInfo(){
  Serial.println("Max motor speed is "+String(getMaxSpeed()));
  Serial.println("Current motor speed is "+String(getMotorSpeed()));
  Serial.println("Speed damping is "+String(getSpeedDamping()));
  Serial.println("Encoder Position is "+String(getEncoderPosition()));
  Serial.println("Go-to position is "+String(getGoToPosition()));
  Serial.println("Speed-feedback gain term is "+String(getSpeedFeedbackGainTerm()));
  Serial.println("P-gain term is "+String(getPGainTerm()));
  Serial.println("I-gain term is "+String(getIGainTerm()));
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

long stepsFromDegrees(float angle){
  return angle/DEGREES_RESOLUTION;
}

double stepsToDegrees(long steps){
  return steps*DEGREES_RESOLUTION;
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
  byte buf[4];
  buf[0] = (byte) value;
  buf[1] = (byte) (value >> 8);
  buf[2] = (byte) (value >> 16);
  buf[3] = (byte) (value >> 24);
  
  Wire.beginTransmission(ADDR);
  Wire.write(byte(command));      // sends command byte
  
  Wire.write(buf[0]);
  
  Wire.write(buf[1]);
  
  Wire.write(buf[2]);
  
  Wire.write(buf[3]);
  
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
