#include "ball.h"
#include "paddle.h"
#include <cmath>

#define SCREEN_HEIGHT 48
#define SCREEN_WIDTH 84

Ball::Ball(int x, int y, int radius) : x(x), y(y), radius(radius)
{
    dx = 1;
    dy = 1;
}

void Ball::move()
{
    x += dx;
    y += dy;
}

bool Ball::checkCollision(const Paddle &paddle)
{
    int paddleX = paddle.getX();
    int paddleY = paddle.getY();
    int paddleWidth = paddle.getWidth();
    int paddleHeight = paddle.getHeight();

    return (x - radius <= paddleX + paddleWidth) && (x + radius >= paddleX) &&
           (y - radius <= paddleY + paddleHeight) && (y + radius >= paddleY);
}

int Ball::checkXWallCollision(int screenWidth)
{
    if (x - radius <= 0)
    {
        return 1;
    }
    else if (x + radius >= screenWidth)
    {

        return 2;
    }
    else
    {
        return 0;
    }
}

bool Ball::checkYWallCollision(int screenHeight)
{
    if (y - radius <= 0) 
    {
        bounceY();
        y += radius;  // Add buffer when bouncing off the top wall
        return true;
    } 
    else if (y + radius >= screenHeight)
    {
        bounceY();
        y -= radius;  // Subtract buffer when bouncing off the bottom wall
        return true;
    }
    return false;
}

void Ball::bounce(const Paddle &paddle)
{
    dx = -dx;
    dy = ((y - (paddle.getY() + paddle.getHeight() / 2)) / static_cast<float>(paddle.getHeight())) * 2;

    // Add a small buffer to the ball's y position after bouncing to prevent it from immediately recolliding with the paddle.
    if (dy > 0) {
        y += radius;
    } else {
        y -= radius;
    }
}

int Ball::getX() const
{
    return x;
}

int Ball::getY() const
{
    return y;
}

int Ball::getRadius() const
{
    return radius;
}

void Ball::bounceX()
{
    dx = -dx;
}

void Ball::bounceY()
{
    dy = -dy;
}

float Ball::getDiameter() const
{
    return 2 * radius;
}

void Ball::reset(){
    y = SCREEN_HEIGHT/2;
    x = SCREEN_WIDTH /2;
}