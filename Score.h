#ifndef SCORE_H
#define SCORE_H

#include "raylib.h"

class Score
{
public:
    int GetScore() { return m_score; }
    void EarnScore();

private:
    int m_score{};
};

#endif