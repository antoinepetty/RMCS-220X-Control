#include "RMCS-220X.h"

long RMCS220X::stepsFromDegrees(double angle) {
    return angle/DEGREES_RESOLUTION;
}

double RMCS220X::stepsToDegrees(long steps) {
    return steps*DEGREES_RESOLUTION;
}

void RMCS220X::write2ByteAttr(byte command, int value) {
  Wire.beginTransmission(i2cAddress);
  Wire.write(byte(command));          // sends command byte
  Wire.write(byte(lowByte(value)));   // sends value byte lsb
  Wire.write(byte(highByte(value)));  // sends value byte msb
  Wire.endTransmission();
}

void RMCS220X::write4ByteAttr(byte command, long value) {
  byte buf[4];
  buf[0] = (byte) value;
  buf[1] = (byte) (value >> 8);
  buf[2] = (byte) (value >> 16);
  buf[3] = (byte) (value >> 24);
  
  Wire.beginTransmission(i2cAddress);
  Wire.write(byte(command));      // sends command byte
  
  Wire.write(buf[0]);
  Wire.write(buf[1]);
  Wire.write(buf[2]);
  Wire.write(buf[3]);
  
  Wire.endTransmission();
}

int RMCS220X::read2ByteAttr(byte command) {
    return (int) readAttr(command, 2);
}

long RMCS220X::read4ByteAttr(byte command) {
    return readAttr(command, 4);
}

long RMCS220X::readAttr(byte command, int numberOfBytes) {
  long result = 0;
  Wire.beginTransmission(i2cAddress);
  Wire.write(byte(command));          // send command byte
  Wire.endTransmission();
  delay(PAUSE_DURATION_MS); // Delay to allow the motor's controller to react to the previous message
  Wire.requestFrom((int) i2cAddress, (int) numberOfBytes);
  if (numberOfBytes <= Wire.available()) { // if correct num of bytes received
    for(int i=0; i<numberOfBytes; i++){
      long currentByte = Wire.read();
      currentByte = currentByte << (8*i);
      result |= currentByte;
    }
    return result;
  }
  else{
    Serial.println("\nERROR: No data received. Available bytes: "+String(Wire.available()));
    return -1;
  }
}

RMCS220X::RMCS220X() {
  // Empty constructor
}

void RMCS220X::begin(byte incomingi2cAddress) {
    Wire.begin(); // join i2c bus
    i2cAddress = incomingi2cAddress; // set motor address
}

void RMCS220X::writeMaxSpeed(int maxSpeed) {
    write2ByteAttr(MAX_SPEED_ATTR, maxSpeed);
}

int RMCS220X::readMaxSpeed() {
    return read2ByteAttr(MAX_SPEED_ATTR);
}

void RMCS220X::writeSpeed(int motorSpeed) {
    write2ByteAttr(SPEED_ATTR, motorSpeed);
}

int RMCS220X::readSpeed() {
    return read2ByteAttr(SPEED_ATTR);
}

void RMCS220X::writeSpeedDamping(int value) {
    write2ByteAttr(SPEED_DAMP_ATTR, value);
}

int RMCS220X::readSpeedDamping() {
    return read2ByteAttr(SPEED_DAMP_ATTR);
}

void RMCS220X::writeSpeedFeedbackGainTerm(int value) {
    write2ByteAttr(SPEED_FDBK_GAIN_TERM_ATTR, value);
}

int RMCS220X::readSpeedFeedbackGainTerm() {
    return read2ByteAttr(SPEED_FDBK_GAIN_TERM_ATTR);
}

void RMCS220X::writePGainTerm(int value) {
    write2ByteAttr(P_GAIN_TERM_ATTR, value);
}

int RMCS220X::readPGainTerm() {
    return read2ByteAttr(P_GAIN_TERM_ATTR);
}

void RMCS220X::writeIGainTerm(int value) {
    write2ByteAttr(I_GAIN_TERM_ATTR, value);
}

int RMCS220X::readIGainTerm() {
    return read2ByteAttr(I_GAIN_TERM_ATTR);
}

void RMCS220X::calibrateEncoderPositionInSteps(long value) {
    write4ByteAttr(ENCODER_POS_ATTR, value);
}

int RMCS220X::readEncoderPositionInSteps() {
    return read4ByteAttr(ENCODER_POS_ATTR);
}

void RMCS220X::goToPositionInSteps(long value) {
    write4ByteAttr(GO_TO_POS_ATTR, value);
}

int RMCS220X::readGoToPositionInSteps() {
    return read4ByteAttr(GO_TO_POS_ATTR);
}

void RMCS220X::goToRelativePositionInSteps(long value) {
    write4ByteAttr(RELATIVE_GO_TO_ATTR, value);
}



void RMCS220X::calibrateEncoderPositionInDegrees(double value) {
    calibrateEncoderPositionInSteps(stepsFromDegrees(value));
}

double RMCS220X::readEncoderPositionInDegrees() {
    return stepsToDegrees(readEncoderPositionInSteps());
}

void RMCS220X::goToPositionInDegrees(double value) {
    goToPositionInSteps(stepsFromDegrees(value));
}

double RMCS220X::readGoToPositionInDegrees() {
    return stepsToDegrees(readGoToPositionInSteps());
}

void RMCS220X::goToRelativePositionInDegrees(double value) {
    goToRelativePositionInSteps(stepsFromDegrees(value));
}


