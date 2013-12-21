#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "PokerPlayer.h"
#include <vector>

namespace pokerGame
{

class GameContext
{
public:
    GameContext(float initialBigBlind);

    int dealerIndex;
    int bigBlindIndex;
    int smallBlindIndex;
    float bigBlind;
    std::vector<PokerPlayer*> players;
};

}

#endif
