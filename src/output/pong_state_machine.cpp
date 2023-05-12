#include "pong_state_machine.h"
#include "Joystick.h"
#include "button.h"
#include "common.h"
#include "calibration.h"
#include "game/ai.h"
#include "./output/display.h"

PongStateMachine::PongStateMachine(

    Display &display,
    N5110 &lcd,
    Joystick &joystick1,
    Joystick &joystick2,
    Scoring &scoring) : currentState(MAIN_MENU),
                        display(display),
                        lcd(lcd),
                        joystick1(joystick1),
                        joystick2(joystick2),
                        scoring(scoring)
{
}

void PongStateMachine::run(volatile int &g_button1_interrupt, volatile int &g_button2_interrupt)
{
    while (true)
    {
        switch (currentState)
        {
        case MAIN_MENU:
            handleMainMenu(g_button1_interrupt,g_button2_interrupt);
            break;
        case SINGLE_PLAYER:
            handleSinglePlayer();
            break;
        case MULTI_PLAYER:
            handleMultiPlayer();
            break;
        case TEST_MODE:
            handleTestMode(g_button1_interrupt);
            break;
        }
    }
}

void PongStateMachine::handleMainMenu(volatile int &g_button1_interrupt, volatile int &g_button2_interrupt)
{

    bool isPressed = false;
    Direction dir = Direction::CENTRE;

    // Create buttons for each menu option
    Button singlePlayerButton("1-P");
    Button twoPlayerButton("2-P");
    Button testButton("Test");

    // Add buttons to a vector
    std::vector<Button> buttons = {singlePlayerButton, twoPlayerButton, testButton};
    int selectedIndex = 0;

    while (currentState == GameState::MAIN_MENU)
    {
        dir = joystick1.get_direction(); // Get the joystick direction

        // Check if the joystick is pressed
        if (g_button1_interrupt || g_button2_interrupt)
        {
            isPressed = true;
            g_button1_interrupt = 0;
            g_button2_interrupt = 0;
        }

        // Change the selected index based on the joystick input
        if (dir == Direction::N && selectedIndex > 0)
        {
            selectedIndex--;
        }
        else if (dir == Direction::S && selectedIndex < buttons.size() - 1)
        {
            selectedIndex++;
        }

        // Call the action function when the joystick is pressed down
        if (isPressed)
        {
            isPressed = false;
            switch (selectedIndex)
            {
            case 0:
                currentState = GameState::SINGLE_PLAYER;
                break;
            case 1:
                currentState = GameState::MULTI_PLAYER;
                break;
            case 2:
                currentState = GameState::TEST_MODE;
                break;

            default:
                break;
            }
        }

        // Update the display with the new menu selection
        display.drawMenu(buttons, selectedIndex);

        wait_us(200000); // Add a small delay to avoid rapid input
    }
}

// General method
void PongStateMachine::handleGame(
    Ball &ball,
    Paddle &playerPaddle1,
    Paddle &playerPaddle2,
    std::function<void(Paddle &, const Ball &)> updateSecondPaddle)
{
    int screenWidth = G_SCREEN_WIDTH;
    int screenHeight = G_SCREEN_HEIGHT;

    Scoring scoring = Scoring();

    int ballCollisionX = 0;

    // Game loop
    while (currentState != GameState::MAIN_MENU)
    {
        if (ball.checkCollision(playerPaddle1))
        {
            ball.bounce(playerPaddle1);
        }
        else if (ball.checkCollision(playerPaddle2))
        {
            ball.bounce(playerPaddle2);
        }else {
            ball.checkYWallCollision(screenHeight);
        }
        
        ballCollisionX = ball.checkXWallCollision(screenWidth);

        if (ballCollisionX != 0)
        {
            scoring.playerScored(ballCollisionX - 1);
            ballCollisionX = 0;
            ball.reset();
            playerPaddle1.reset();
            playerPaddle2.reset();
        }

        // Check for end game condition
        if (scoring.hasWinner())
        {
            currentState = GameState::MAIN_MENU;
            break;
        }

        // Update player paddles
        playerPaddle1.move(gameMoveJoystick(joystick1));
        updateSecondPaddle(playerPaddle2, ball);
        ball.move();

        // Draw game objects
        display.drawSprites(ball, playerPaddle1, playerPaddle2, scoring);

        wait_us(5000);
    }
}

// Single player
void PongStateMachine::handleSinglePlayer()
{
    int screenWidth = G_SCREEN_WIDTH;
    int screenHeight = G_SCREEN_HEIGHT;
    Ball ball(screenWidth / 2, screenHeight / 2, 3);
    Paddle playerPaddle1(10 + 2, screenHeight / 2 - 5, 3, 5);
    Paddle aiPaddle(screenWidth - 10 - 2, screenHeight / 2 - 5, 3, 5);
    AI ai(aiPaddle, ball, screenHeight);
    currentState = GameState::SINGLE_PLAYER;
    handleGame(ball, playerPaddle1, aiPaddle, [&ai](Paddle &paddle, const Ball &ball)
               { ai.update(); });
}

// Multi-player
void PongStateMachine::handleMultiPlayer()
{
    int screenWidth = G_SCREEN_WIDTH;
    int screenHeight = G_SCREEN_HEIGHT;
    Ball ball(screenWidth / 2, screenHeight / 2, 3);
    Paddle playerPaddle1(10 + 2, screenHeight / 2 - 5, 3, 5);
    Paddle playerPaddle2(screenWidth - 10 - 2, screenHeight / 2 - 5, 3, 5);
    currentState = GameState::MULTI_PLAYER;
    handleGame(ball, playerPaddle1, playerPaddle2, [this](Paddle &paddle, const Ball &ball)
               { paddle.move(gameMoveJoystick(joystick2)); });
}

void PongStateMachine::handleTestMode(volatile int &interrupt)
{
    //make sure interrupt is at 0
    interrupt = 0;
    Calibration calibration;
    wait_us(500);
    printf("Calibrating Joystick 1\n");
    wait_us(500);
    bool joystick1CalibrationResult =  calibration.testJoystickY(joystick1);
    wait_us(500);

    wait_us(500);
    if (joystick1CalibrationResult){
        printf("Calibration Successful\n");
    } else {
        printf("Calibration Failed\n");
    }
    wait_us(500);

    printf("Calibrating Joystick 2\n");
    wait_us(500);
    bool joystick2CalibrationResult =  calibration.testJoystickY(joystick2);
    wait_us(500);
    if (joystick2CalibrationResult){
        printf("Calibration Successful\n");
    } else {
        printf("Calibration Failed\n");
    }
    wait_us(500);
    printf("Calibration Complete\n"); 

    wait_us(500);

    printf("Calibrating Screen\n"); 
    calibration.calibrateLCD(lcd, joystick1, interrupt);

    wait_us(500);

    currentState = GameState::MAIN_MENU;
}

int PongStateMachine::gameMoveJoystick(Joystick& joystick){
    if(joystick.get_direction() == N){
          return 2;

        }else if(joystick.get_direction() == S){
            return -2;
        
        }else if(joystick.get_direction() == NE){
            return 2;
        }else if(joystick.get_direction() == NW){
           return 2;

        }else if(joystick.get_direction() == SE){
           return -2;

        }else if(joystick.get_direction() == SW){
            return -2;
        } 

    return 0;
}