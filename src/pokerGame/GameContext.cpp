#include "pokerGame/GameContext.h"

namespace pokerGame
{

GameContext::GameContext(float initialBigBlind) : bigBlind(initialBigBlind), dealerIndex(-1), bigBlindIndex(-1), smallBlindIndex(-1), players()
{
}

}
