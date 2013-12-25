#ifndef PREFLOPSIMULATOR_H
#define PREFLOPSIMULATOR_H

#include "pokerGame/simulation/HoleCardsEquivalence.h"
#include "pokerGame/simulation/WinningStatistics.h"
#include "pokerGame/PlayerController.h"
#include "pokerGame/BettingRound.h"
#include "pokerGame/GameRound.h"
#include "pokerGame/card/Deck.h"
#include "pokerGame/simulation/PreFlopStatistics.h"
#include <vector>

namespace pokerGame {
namespace simulation {

class PreFlopSimulator
{
public:
    PreFlopSimulator();
    ~PreFlopSimulator();

    void simulate();

private:
    void generateAllHoleCardsEquivalences();
    void generateAllPairsEquivalences();
    void generateNotPairEquivalences();

    std::vector<HoleCardsEquivalence*> holeCardsEquivalences;
    WinningStatistics statisticsController;
    PlayerController* playerController;
    GameRound* gameRoundSimulator;
    card::Deck* deck;
    BettingRound* bettingRound;
    PreFlopStatistics statistics;
    std::map<std::pair<HoleCardsEquivalence*, int>, double> percentageOfWinning;

    static const int MAX_NUMBER_OF_PLAYERS;
    static const int NUMBER_OF_SIMULATIONS;
};

}
}



#endif
