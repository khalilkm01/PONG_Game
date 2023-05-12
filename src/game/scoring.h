#ifndef SCORING_H
#define SCORING_H

class Scoring
{
public:
    Scoring();
    void playerScored(int playerIndex);
    bool hasWinner();
    int getWinner();
    int getScore(int playerIndex);
    static const int WINNING_SCORE = 10;

private:
    int scores[2];
};

#endif // SCORING_H