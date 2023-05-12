#include "display.h"
#include "common.h"
#include <cstdio>
#define SCREEN_HEIGHT 48
#define SCREEN_WIDTH 84

Display::Display(N5110 &lcd) : lcd(lcd) {}

void Display::drawSprites(Ball &ball, Paddle &paddle1, Paddle &paddle2, Scoring &scoring)
{
    clearScreen();

    // Draw ball
    lcd.drawCircle(ball.getX(), ball.getY(), ball.getRadius(), FILL_BLACK);

    // Draw paddles
    lcd.drawRect(paddle1.getX(), paddle1.getY(), paddle1.getWidth(), paddle1.getHeight(), FILL_BLACK);
    lcd.drawRect(paddle2.getX(), paddle2.getY(), paddle2.getWidth(), paddle2.getHeight(), FILL_BLACK);

    // Display scores
    char buffer1[16];
    char buffer2[16];
    sprintf(buffer1, "%d", scoring.getScore(1));
    sprintf(buffer2, "%d", scoring.getScore(0));
    char* result1 = buffer1;
    char* result2 = buffer2;

    // printf("%s", result1);
    // printf("%s", result2);

    lcd.printString(result1, 5, 0);
    lcd.printString(result2, SCREEN_WIDTH - 5, 0);

    refreshScreen();
}

void Display::drawMenu(std::vector<Button> &buttons, int selectedIndex)
{
    clearScreen();

    int screenWidth = G_SCREEN_HEIGHT;
    int screenHeight = G_SCREEN_WIDTH;

    for (size_t i = 0; i < buttons.size(); ++i)
    {
        int buttonY = 10 + i * 12;

        // Draw the button rectangle
        if (selectedIndex == i)
        {
            lcd.drawRect(0, buttonY - 2, screenWidth, 10, FILL_BLACK);
        }
        
        lcd.printString(buttons[i].getText().c_str(), SCREEN_WIDTH - 22, ((i+1)*2)-1);
        
     
    }

    refreshScreen();
}

void Display::clearScreen()
{
    lcd.clear();
}

void Display::refreshScreen()
{
    lcd.refresh();
}
