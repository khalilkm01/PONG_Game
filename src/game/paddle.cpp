#include "paddle.h"
#include "mbed.h"
#include <string>
#define SCREEN_HEIGHT 48

Paddle::Paddle(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

void Paddle::setPosition(int newY) {
    y = clamp(newY, 0, SCREEN_HEIGHT - height);
}

void Paddle::move(int joystickValue) {
    // Adjust position based on joystick input
    // char buffer[16];
    // sprintf(buffer, "%d", joystickValue);
    // char* result = buffer;
    // printf("%s", result);
    int y = getY();
    int width = getWidth();


    setPosition(y + joystickValue);
}

int Paddle::clamp(int value, int min, int max)
{
    if (value < min)
    {
        return min;
    }
    else if (value > max)
    {
        return max;
    }
    return value;
}


int Paddle::getX() const {
    return x;
}

int Paddle::getY() const {
    return y;
}

int Paddle::getWidth() const {
    return width;
}

int Paddle::getHeight() const {
    return height;
}

void Paddle::reset() {
    y=SCREEN_HEIGHT/2 - width;
}