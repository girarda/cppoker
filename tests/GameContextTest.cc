#include "gtest/gtest.h"
#include "pokerGame/GameContext.h"


class GameContextTest : public ::testing::Test {

protected:
    pokerGame::GameContext* context;

    static const int BIG_BLIND;
    static const int DEALER_INDEX;
    static const int BIG_BLIND_INDEX;
    static const int SMALL_BLIND_INDEX;

    virtual void SetUp() {
        context = new pokerGame::GameContext(BIG_BLIND);
    }
    virtual void TearDown() {
        delete context;
    }

};

const int GameContextTest::BIG_BLIND(2);
const int GameContextTest::DEALER_INDEX(0);
const int GameContextTest::BIG_BLIND_INDEX(1);
const int GameContextTest::SMALL_BLIND_INDEX(0);

TEST_F(GameContextTest, newGameHasNoPlayers) {

}
