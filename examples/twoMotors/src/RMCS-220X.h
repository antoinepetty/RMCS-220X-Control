#ifndef RMCS220X_H
#define RMCS220X_H

#include <Arduino.h> 
#include <Wire.h>

// The command byte values (Each attribute you can read/write)
#define MAX_SPEED_ATTR 0
#define SPEED_ATTR 1
#define SPEED_DAMP_ATTR 2
#define ENCODER_POS_ATTR 3
#define GO_TO_POS_ATTR 4
#define SPEED_FDBK_GAIN_TERM_ATTR 5
#define P_GAIN_TERM_ATTR 6
#define I_GAIN_TERM_ATTR 7
#define RELATIVE_GO_TO_ATTR 8

#define DEGREES_RESOLUTION 0.2 // Each step of the motor is this many degrees

class RMCS220X{
    private:
        byte i2cAddress = 0x10; // Default address for this motor is 0x10

        long stepsFromDegrees(double angle);

        double stepsToDegrees(long steps);

        /* writes any 2 byte attribute */
        void write2ByteAttr(byte command, int value);

        /* writes any 4 byte attribute */
        void write4ByteAttr(byte command, long value);

        /* reads any 2 byte attribute */
        int read2ByteAttr(byte command);

        /* reads any 4 byte attribute */
        long read4ByteAttr(byte command);

        /* read the value of any attribute */
        long readAttr(byte command, int numberOfBytes);

    public:
        
        RMCS220X();

        /* connect to i2c bus */
        void begin(byte incomingi2cAddress);

        /* write the maximum speed of the motor (0 to 255) */
        void writeMaxSpeed(int maxSpeed);

        /* read the maximum speed of the motor (0 to 255) */
        int readMaxSpeed();

        /* write the speed/direction of the motor (-255 to 255) */
        void writeSpeed(int motorSpeed);

        /* read the speed/direction of the motor (-255 to 255) */
        int readSpeed();

        /* write the speed damping (0 to 255) */
        void writeSpeedDamping(int value);

        /* read the speed damping (0 to 255) */
        int readSpeedDamping();

        /* write the speed feedback gain term (0 to 32767) */
        void writeSpeedFeedbackGainTerm(int value);

        /* read the speed feedback gain term (0 to 32767) */
        int readSpeedFeedbackGainTerm();

        /* write the p-gain term (0 to 32767) */
        void writePGainTerm(int value);

        /* read the p-gain term (0 to 32767) */
        int readPGainTerm();

        /* write the i-gain term (0 to 32767) */
        void writeIGainTerm(int value);

        /* read the i-gain term (0 to 32767) */
        int readIGainTerm();

        /* set the current motor position as (-2147483647 to 2147483647) */
        void calibrateEncoderPositionInSteps(long value);

        /* read the encoder position (-2147483647 to 2147483647) */
        int readEncoderPositionInSteps();

        /* write the "go to" position (-2147483647 to 2147483647) */
        void goToPositionInSteps(long value);

        /* read the "go to" position (-2147483647 to 2147483647) */
        int readGoToPositionInSteps();

        /* write the relative "go to" position (-2147483647 to 2147483647) */
        void goToRelativePositionInSteps(long value);    



        /* set the current motor position as (-429496729.0 to 429496729.0) */
        void calibrateEncoderPositionInDegrees(double value);

        /* read the encoder position (-429496729.0 to 429496729.0) */
        double readEncoderPositionInDegrees();

        /* write the "go to" position (-429496729.0 to 429496729.0) */
        void goToPositionInDegrees(double value);

        /* read the "go to" position (-429496729.0 to 429496729.0) */
        double readGoToPositionInDegrees();

        /* write the relative "go to" position (-429496729.0 to 429496729.0) */
        void goToRelativePositionInDegrees(double value);    


};

#endif /* RMCS220X_H */
