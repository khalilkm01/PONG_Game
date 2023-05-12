#ifndef POWERUP_H
#define POWERUP_H

#include "ball.h"
#include "paddle.h"

class PowerUp {
public:
    virtual ~PowerUp() {}
    virtual void activate(Paddle& paddle, Ball& ball) = 0;
    virtual void deactivate(Paddle& paddle, Ball& ball) = 0;
};

#endif // POWERUP_H