#include "Joystick.h"
#include "N5110.h"
#include "mbed.h"

#include "./output/pong_state_machine.h"
#include "./output/display.h"



//                  y     x
Joystick joystick_1(PC_1, PC_0);  //attach and create joystick object
InterruptIn joystick_1_button(PB_12);

volatile int g_button1_interrupt = 0;
void joystick1_button_isr();

//                  y     x
Joystick joystick_2(PA_0, PA_1);  //attach and create joystick object
InterruptIn joystick_2_button(PC_13);
volatile int g_button2_interrupt = 0;
void joystick2_button_isr();

//Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)  
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);

// main() runs in its own thread in the OS
int main()
{
    joystick_1.init();
    joystick_2.init();
    lcd.init(LPH7366_1);
    lcd.setContrast(0.55);
    lcd.setBrightness(0.5);
    lcd.clear();

    joystick_1_button.fall(&joystick1_button_isr);
    joystick_2_button.fall(&joystick2_button_isr);
    joystick_1_button.mode(PullUp);
    joystick_2_button.mode(PullUp);


    wait_ns(500);
    Scoring scoring;
    Display display(lcd);
    PongStateMachine pong_state_machine(display, lcd, joystick_1, joystick_2, scoring);
    while (true) {
        pong_state_machine.run(g_button1_interrupt,g_button2_interrupt);
    }
}

void joystick1_button_isr(){
    g_button1_interrupt=1;
}

void joystick2_button_isr(){
    g_button2_interrupt=1;
}