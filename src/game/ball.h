#ifndef BALL_H
#define BALL_H

#include "paddle.h"

class Ball
{
public:
    Ball(int x, int y, int radius);
    void move();
    bool checkCollision(const Paddle &paddle);
    void bounce(const Paddle &paddle);
    int getX() const;
    int getY() const;
    int getRadius() const;
    int checkXWallCollision(int screenWidth);
    bool checkYWallCollision(int screenHeight);
    float getDiameter() const;
    void bounceX();
    void bounceY();
    void reset();

private:
    int x, y;
    int radius;
    int dx, dy;
};

#endif // BALL_H
