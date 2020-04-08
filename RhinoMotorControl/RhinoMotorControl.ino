#include <Wire.h>

#define ADDR 0x08 //Default address

#define MAX_SPEED_ATTR 0
#define SPEED_ATTR 1
#define SPEED_DAMP_ATTR 2
#define ENCODER_POS_ATTR 3
#define GO_TO_POS_ATTR 4
#define SPEED_FDBK_GAIN_TERM_ATTR 5
#define P_GAIN_TERM_ATTR 6
#define I_GAIN_TERM_ATTR 7
#define RELATIVE_GO_TO_ATTR 8

void setup() {
  Serial.begin(9600);
  Serial.println("Starting i2c connection...");
  Wire.begin(); // join i2c bus

  Serial.println("Speed is " + String(getMotorSpeed()));
  Serial.println("Setting speed to 150");
  setMotorSpeed(150);
  delay(2000);
  Serial.println("Speed is " + String(getMotorSpeed()));
  Serial.println("Setting speed to 0");
  setMotorSpeed(0);
  delay(2000);
  Serial.println("Speed is " + String(getMotorSpeed()));
  Serial.println("Setting speed to -150");
  setMotorSpeed(-150);
  delay(2000);
  Serial.println("Speed is " + String(getMotorSpeed()));
  Serial.println("Setting speed to 0");
  setMotorSpeed(150);
  delay(2000);
  Serial.println("Speed is " + String(getMotorSpeed()));
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
  get2ByteAttr(SPEED_ATTR);
}

/* Set the maximum speed of the motor (0 to 255) */
void setMaxSpeed(int maxSpeed){
  set2ByteAttr(MAX_SPEED_ATTR, maxSpeed);
}

/* Set the speed damping (0 to 255) */
void setSpeedDamping(int value){
  set2ByteAttr(SPEED_DAMP_ATTR, value);
}

/* Set the speed feedback gain term (0 to 32767) */
void setSpeedFeedbackGainTerm(int value){
  set2ByteAttr(SPEED_FDBK_GAIN_TERM_ATTR, value);
}

/* Set the p-gain term (0 to 32767) */
void setPGainTerm(int value){
  set2ByteAttr(P_GAIN_TERM_ATTR, value);
}

/* Set the i-gain term (0 to 32767) */
void setIGainTerm(int value){
  set2ByteAttr(I_GAIN_TERM_ATTR, value);
}

/* Set the encoder position (-2147483647 to 2147483647) */
void setEncoderPosition(long value){
  set4ByteAttr(ENCODER_POS_ATTR, value);
}

/* Set the "go to" position (-2147483647 to 2147483647) */
void goToPosition(long value){
  set4ByteAttr(GO_TO_POS_ATTR, value);
}

/* Set the relative "go to" position (-2147483647 to 2147483647) */
void goToRelativePosition(long value){
  set4ByteAttr(RELATIVE_GO_TO_ATTR, value);
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
void get2ByteAttr(byte command){
  getAttr(command, 2);
}

/* Gets any 4 byte attribute */
void get4ByteAttr(byte command){
  getAttr(command, 4);
}

/* Get the value of any attribute */
long getAttr(byte command,int numberOfBytes){
  long result = 0;
  Serial.println("Sending command "+String(command));
  Wire.beginTransmission(ADDR);
  Wire.write(byte(command));          // sends command byte
  Wire.write(byte(0));          // sends dummy byte
  Wire.endTransmission();
  
  Wire.requestFrom(ADDR, numberOfBytes);
  Serial.println("Waiting to receive "+String(numberOfBytes)+" bytes...");
  Serial.println("Currently "+String(Wire.available())+" bytes available");
  while(numberOfBytes > Wire.available()){
    //Serial.println("Waiting for enough bytes");
  }
  if (numberOfBytes <= Wire.available()) { // if correct num of bytes received
      for(int i=0; i<numberOfBytes; i++){
        long currentByte = Wire.read();
        Serial.println("Received byte: "+String(currentByte));
        currentByte = currentByte << 8*i;
        result |= currentByte;
      }
    }
  
  return result;
}
