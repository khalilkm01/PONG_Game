#include "scoring.h"

Scoring::Scoring()
{
    scores[0] = 0;
    scores[1] = 0;
}

void Scoring::playerScored(int playerIndex)
{
    if (playerIndex >= 0 && playerIndex < 2)
    {
        scores[playerIndex]++;
    }
}

bool Scoring::hasWinner()
{
    return scores[0] >= WINNING_SCORE || scores[1] >= WINNING_SCORE;
}

int Scoring::getWinner()
{
    if (scores[0] >= WINNING_SCORE)
    {
        return 1;
    }
    else if (scores[1] >= WINNING_SCORE)
    {
        return 2;
    }
    return 0;
}

int Scoring::getScore(int playerIndex)
{
    if (playerIndex >= 0 && playerIndex < 2)
    {
        return scores[playerIndex];
    }
    return 0;
}
