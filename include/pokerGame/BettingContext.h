#ifndef BETTINGCONTEXT_H
#define BETTINGCONTEXT_H

#include <vector>
#include "GameContext.h"

class BettingContext
{
public:
    BettingContext();


private:
    std::vector<Card> sharedCards;
    GameContext gameContext;
};

#endif
