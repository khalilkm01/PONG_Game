#ifndef PONG_STATE_MACHINE_H
#define PONG_STATE_MACHINE_H

#include "display.h"
#include "game_state.h"
#include "Joystick.h"
#include "game/ball.h"
#include "game/paddle.h"
#include "game/powerup.h"
#include "game/scoring.h"

class PongStateMachine
{
public:
    PongStateMachine(
        Display& display,
        N5110& lcd,
        Joystick& joystick1,
        Joystick& joystick2,
        Scoring& scoring);

    void run(
        volatile int &button1_interrupt,
        volatile int &button2_interrupt
    );

private:
    void handleMainMenu(
        volatile int &button1_interrupt,
        volatile int &button2_interrupt
    );
    void handleSinglePlayer();
    void handleMultiPlayer();
    void handleTestMode(volatile int &interrupt);
    void handleGame(
        Ball &ball,
        Paddle &playerPaddle1,
        Paddle &playerPaddle2,
        std::function<void(Paddle &, const Ball &)> updateSecondPaddle);
    int gameMoveJoystick(Joystick& joystick);

    GameState currentState;
    Display& display;
    N5110& lcd;
    Joystick& joystick1;
    Joystick &joystick2;
    Scoring& scoring;
};

#endif // PONG_STATE_MACHINE_H
