#include "gtest/gtest.h"
#include "pokerGame/simulation/PreFlopStatistics.h"
#include "tests/mocks/pokerGame/simulation/HoleCardsEquivalenceMock.h"

using ::testing::Return;
using ::testing::_;

class PreFlopStatisticsTest : public ::testing::Test {
protected:
    test::HoleCardsEquivalenceMock* holeCardsEquivalence;
    pokerGame::simulation::PreFlopStatistics preFlopStatistics;

    static const int A_NUMBER_OF_PLAYERS;
    static const double A_PROBABILITY;

    virtual void SetUp() {
        holeCardsEquivalence = new test::HoleCardsEquivalenceMock();

    }
    virtual void TearDown() {
        delete holeCardsEquivalence;
    }
};

const int PreFlopStatisticsTest::A_NUMBER_OF_PLAYERS(2);
const double PreFlopStatisticsTest::A_PROBABILITY(1.5);

TEST_F(PreFlopStatisticsTest, canGetStoredWinningProbabilities) {
    preFlopStatistics.addWinningProbability(holeCardsEquivalence, A_NUMBER_OF_PLAYERS, A_PROBABILITY);
    double p = preFlopStatistics.getWinningProbability(holeCardsEquivalence, A_NUMBER_OF_PLAYERS);
    ASSERT_EQ(A_PROBABILITY, p);
}
