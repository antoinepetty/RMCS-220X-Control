# Control for Rhino High-Torque Encoder DC Servo Motor and Driver (RMCS-220X)

This code requires you use the i2c interface connected as in the manual: https://robokits.download/downloads/RMCS220x_DCServo_Driver.pdf

You must pull up the SDA and SCL pins on your Arduino to 5v with 4.7k resistors.

## Functionality

As per the manual, you are able to perform the following functions:

- Read/Write Motor Speed and Direction
- Read/Write Speed Damping
- Read/Write Encoder Position
- Read/Write Go to Position Command
- Read/Write Speed-Feedback Gain term
- Read/Write P-Gain term
- Read/Write I-Gain term
- Write Relative Go to Position Command

Please see `src/RMCS-220X.h` for the relevant methods, data types and accepted parameters.
