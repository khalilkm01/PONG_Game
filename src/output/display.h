#ifndef DISPLAY_H
#define DISPLAY_H

#include "N5110.h"
#include "game/ball.h"
#include "game/paddle.h"
#include "button.h"
#include "game/scoring.h"
#include <vector>

#define G_SCREEN_HEIGHT 48
#define G_SCREEN_WIDTH 84

class Display {
public:
    Display(N5110& lcd);
    void drawSprites(Ball& ball, Paddle& paddle1, Paddle& paddle2, Scoring &scoring);
    void drawMenu(std::vector<Button>& buttons, int selectedIndex);
    void clearScreen();
    void refreshScreen();

private:
    N5110& lcd;
};

#endif // DISPLAY_H
