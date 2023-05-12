#ifndef PADDLE_H
#define PADDLE_H

class Paddle
{
public:
    Paddle(int x, int y, int width, int height);

    void setPosition(int newY);
    void move(int joystickValue);
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    void reset();

private:
    int x, y;
    int width, height;
    int clamp(int value, int min, int max);
};

#endif // PADDLE_H
