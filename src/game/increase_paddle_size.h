#ifndef INCREASE_PADDLE_SIZE_H
#define INCREASE_PADDLE_SIZE_H

#include "powerup.h"

class IncreasePaddleSize : public PowerUp {
public:
    void activate(Paddle& paddle, Ball& ball) override;
    void deactivate(Paddle& paddle, Ball& ball) override;
};

#endif // INCREASE_PADDLE_SIZE_H
