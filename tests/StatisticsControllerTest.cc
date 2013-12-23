#include "gtest/gtest.h"
#include "PlayerMock.h"
#include "pokerGame/simulator/StatisticsController.h"

using ::testing::Return;
using ::testing::_;

class StatisticsControllerTest : public ::testing::Test {
protected:
    test::PlayerMock* aPlayer;
    pokerGame::simulator::StatisticsController statisticsController;

    static const int ZERO_WIN;
    static const int ONE_WIN;

    virtual void SetUp() {
        aPlayer = new test::PlayerMock();

    }
    virtual void TearDown() {
        delete aPlayer;
    }
};

const int StatisticsControllerTest::ZERO_WIN(0);
const int StatisticsControllerTest::ONE_WIN(1);

TEST_F(StatisticsControllerTest, ifPlayerHasNoStoredWinsThenGetPlayerWinsReturns0) {
    int numberOfWins = statisticsController.getPlayerWins(aPlayer);
    ASSERT_EQ(ZERO_WIN, numberOfWins);
}

TEST_F(StatisticsControllerTest, canStorePlayersWins) {
    statisticsController.incrementWins(aPlayer);
    int numberOfWins = statisticsController.getPlayerWins(aPlayer);
    ASSERT_EQ(ONE_WIN, numberOfWins);
}

TEST_F(StatisticsControllerTest, resetResetsTheNumberOfWinsToZero) {
    statisticsController.incrementWins(aPlayer);
    statisticsController.reset();
    int numberOfWins = statisticsController.getPlayerWins(aPlayer);
    ASSERT_EQ(ZERO_WIN, numberOfWins);
}

