#ifndef PREFLOPSIMULATOR_H
#define PREFLOPSIMULATOR_H

#include "pokerGame/HoleCardsEquivalence.h"
#include "pokerGame/simulator/StatisticsController.h"
#include "pokerGame/PlayerController.h"
#include "pokerGame/BettingRound.h"
#include "pokerGame/GameRound.h"
#include "pokerGame/Deck.h"
#include "pokerGame/simulator/PreFlopStatistics.h"
#include <vector>

namespace pokerGame {
namespace simulator {

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

    void save();
    void load();

    std::vector<HoleCardsEquivalence*> holeCardsEquivalences;
    StatisticsController statisticsController;
    PlayerController* playerController;
    GameRound* gameRoundSimulator;
    Deck* deck;
    BettingRound* bettingRound;
    PreFlopStatistics statistics;
    std::map<std::pair<HoleCardsEquivalence*, int>, double> percentageOfWinning;

    static const int MAX_NUMBER_OF_PLAYERS;
    static const int NUMBER_OF_SIMULATIONS;
};

}
}



#endif
