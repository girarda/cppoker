#ifndef SIMULATORGAMEROUNDPREFLOPSIMULATOR_H
#define SIMULATORGAMEROUNDPREFLOPSIMULATOR_H

#include "pokerGame/simulation/HoleCardsEquivalence.h"
#include "pokerGame/card/Deck.h"
#include "pokerGame/BettingRound.h"
#include "pokerGame/GameRound.h"

namespace pokerGame {
namespace simulation {

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
