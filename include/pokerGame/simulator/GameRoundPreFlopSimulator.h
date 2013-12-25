#ifndef SIMULATORGAMEROUNDPREFLOPSIMULATOR_H
#define SIMULATORGAMEROUNDPREFLOPSIMULATOR_H

#include "pokerGame/HoleCardsEquivalence.h"
#include "pokerGame/card/Deck.h"
#include "pokerGame/BettingRound.h"
#include "pokerGame/GameRound.h"

namespace pokerGame {
namespace simulator {

class GameRoundPreFlopSimulator : public GameRound {
public:
    GameRoundPreFlopSimulator(card::Deck *deckToUse, BettingRound* bettingRoundToUse, HoleCardsEquivalence* equivalence);

protected:
    virtual void distributeHoles();

private:
    HoleCardsEquivalence* holeCardsEquivalence;
};

}
}

#endif
