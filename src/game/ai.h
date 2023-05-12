#ifndef AI_H
#define AI_H

#include "paddle.h"
#include "ball.h"
#include <algorithm>
#include <cmath>

class AI
{
public:
    AI(Paddle &aiPaddle, Ball &ball, int screenHeight, float delayFactor = 2.0f);
    void update();

private:
    Paddle &aiPaddle;
    Ball &ball;
    int screenHeight;
    float delayFactor;
};

#endif // AI_H
