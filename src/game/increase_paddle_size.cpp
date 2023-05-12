#include "increase_paddle_size.h"
#include "paddle.h"

void IncreasePaddleSize::activate(Paddle& paddle, Ball& ball) {
    paddle.setPosition(paddle.getHeight() * 2);
}

void IncreasePaddleSize::deactivate(Paddle& paddle, Ball& ball) {
    paddle.setPosition(paddle.getHeight() / 2);
}