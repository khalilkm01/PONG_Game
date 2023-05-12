#include "ai.h"
#include <algorithm>
#include <cmath>

AI::AI(Paddle &aiPaddle, Ball &ball, int screenHeight, float delayFactor)
    : aiPaddle(aiPaddle), ball(ball), screenHeight(screenHeight), delayFactor(delayFactor)
{
}

void AI::update()
{
    int targetY = ball.getY() + ball.getRadius();              // Center of the ball's y-position
    int currentY = aiPaddle.getY() + aiPaddle.getHeight() / 2; // Center of the paddle's y-position
    int deltaY = targetY - currentY;

    int moveY = deltaY * delayFactor; // Apply the delay factor to slow down the AI's reaction time
    int newY = aiPaddle.getY() + moveY;

    newY = std::max(0, std::min(screenHeight - aiPaddle.getHeight(), newY)); // Limit the paddle's position within the screen
    aiPaddle.setPosition(newY);
}
