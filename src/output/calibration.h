#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "N5110.h"
#include "Joystick.h"

class Calibration {
public:
    Calibration();
    bool testJoystickY(Joystick& joystick);
    void calibrateLCD(N5110& lcd, Joystick& joystick,  volatile int &interrupt);


};

#endif // CALIBRATION_H