#include "calibration.h"
#include "Joystick.h"
#include "mbed.h"

Calibration::Calibration(){}

void Calibration::calibrateLCD(N5110& lcd, Joystick& joystick, volatile int &interrupt){
    float brightness = 0.5;
    float contrast = 0.55;
    printf("Move North/South to increase/decrease contrast\n");
    printf("Press down on joystick to continue\n");
    while (interrupt != 1){
        if (joystick.get_direction() == N){
            if (contrast < 1){
                contrast = contrast + 0.05;
            }
        
        } else if (joystick.get_direction() == S){
            if (contrast > 0){
                contrast = contrast - 0.05;
            }
        }
        lcd.setContrast(contrast);
        wait_us(50000);
    }
    //Can't forget to reset the interrupt
    interrupt = 0;

    printf("Move North/South to increase/decrease brightness\n");
    printf("Press down on joystick to continue\n");
    while (interrupt != 1){
        if (joystick.get_direction() == N){
            if (brightness < 1){
                brightness = brightness + 0.05;
            }
        
        } else if (joystick.get_direction() == S){
            if (brightness > 0){
                brightness = brightness - 0.05;
                
            }
        }
        lcd.setBrightness(brightness);
        wait_us(50000);
    }
    //Can't forget to reset the interrupt
    interrupt = 0;

    printf("Screen calibration complete\n");
}

bool Calibration::testJoystickY(Joystick &joystick){
    printf("Move joystick North\n");

    while (joystick.get_direction() != N){
        wait_ns(500);
    }
    wait_us(500);
    printf("Move joystick South\n");

    while (joystick.get_direction() != S){
        wait_ns(500);
    }
    wait_us(500);
    return true;
}