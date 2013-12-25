#ifndef PREFLOPSTATISTICSMOCK_H
#define PREFLOPSTATISTICSMOCK_H

#include "pokerGame/simulation/PreFlopStatistics.h"
#include "gmock/gmock.h"

namespace test {

class PreFlopStatisticsMock : public pokerGame::simulation::PreFlopStatistics {
public:
    MOCK_METHOD2(getWinningProbability, double(pokerGame::simulation::HoleCardsEquivalence* holeCardsEquivalence, int numberOfPlayers));
    MOCK_METHOD3(addWinningProbability, void(pokerGame::simulation::HoleCardsEquivalence* holeCardsEquivalence, int numberOfPlayers, double p));
    MOCK_METHOD1(load, void(std::string file));
    MOCK_METHOD1(save, void(std::string file));
};

}

#endif
