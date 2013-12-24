#include "gtest/gtest.h"
#include "pokerGame/context/BettingContext.h"
#include "pokerGame/BettingRoundType.h"

namespace tests {

class BettingContextTest : public ::testing::Test {
protected:
    static const int A_LOW_NUMBER_OF_RAISES;
    static const int A_HIGH_NUMBER_OF_RAISES;
    static const int A_LOW_NUMBER_OF_PLAYERS;
    static const int A_HIGH_NUMBER_OF_PLAYERS;
    static const pokerGame::BettingRoundType A_BETTING_ROUND_TYPE;
};

const int BettingContextTest::A_LOW_NUMBER_OF_RAISES(2);
const int BettingContextTest::A_HIGH_NUMBER_OF_RAISES(4);
const int BettingContextTest::A_LOW_NUMBER_OF_PLAYERS(2);
const int BettingContextTest::A_HIGH_NUMBER_OF_PLAYERS(4);
const pokerGame::BettingRoundType BettingContextTest::A_BETTING_ROUND_TYPE(pokerGame::PRE_FLOP);


TEST_F(BettingContextTest, bettingContextDoesNotHaveManyRaisesIfNumbeOfRaisesIsLowerThan2) {
    pokerGame::context::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_LOW_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS);
    bool hasManyRaises = bettingContext.hasManyRaises();
    ASSERT_FALSE(hasManyRaises);
}

TEST_F(BettingContextTest, bettingContextHasManyRaisesIfNumbeOfRaisesIsHigherThan2) {
    pokerGame::context::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_HIGH_NUMBER_OF_RAISES, A_LOW_NUMBER_OF_PLAYERS);
    bool hasManyRaises = bettingContext.hasManyRaises();
    ASSERT_TRUE(hasManyRaises);
}

TEST_F(BettingContextTest, bettingContextDoesNotHaveManyPlayersIfNumbeOfPlayersIsLowerThan2) {
    pokerGame::context::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_HIGH_NUMBER_OF_RAISES, A_LOW_NUMBER_OF_PLAYERS);
    bool hasManyPlayers = bettingContext.hasManyPlayers();
    ASSERT_FALSE(hasManyPlayers);
}

TEST_F(BettingContextTest, bettingContextHasManyPlayersIfNumbeOfPlayersIsHigherThan3) {
    pokerGame::context::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_LOW_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS);
    bool hasManyPlayers = bettingContext.hasManyPlayers();
    ASSERT_TRUE(hasManyPlayers);
}

TEST_F(BettingContextTest, canGetBettingRoundType) {
    pokerGame::context::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_LOW_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS);
    pokerGame::BettingRoundType returnedBettingType = bettingContext.getBettingRoundType();
    ASSERT_EQ(A_BETTING_ROUND_TYPE, returnedBettingType);
}

TEST_F(BettingContextTest, canGetNumberOfRaises) {
    pokerGame::context::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_LOW_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS);
    int numberOfRaises = bettingContext.getNumberOfRaises();
    ASSERT_EQ(A_LOW_NUMBER_OF_RAISES, numberOfRaises);
}

TEST_F(BettingContextTest, canGetNumberOfPlayers) {
    pokerGame::context::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_LOW_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS);
    int numberOfPlayers = bettingContext.getNumberOfPlayers();
    ASSERT_EQ(A_HIGH_NUMBER_OF_PLAYERS, numberOfPlayers);
}

TEST_F(BettingContextTest, twoBettingContextsAreEqualsIfEveryMembersAreQeuals) {
    pokerGame::context::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_LOW_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS);
    pokerGame::context::BettingContext anotherContext(A_BETTING_ROUND_TYPE, A_LOW_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS);
    ASSERT_EQ(bettingContext, anotherContext);
}

TEST_F(BettingContextTest, twoBettingContextsAreNotEqualsIfEveryMembersAreNotEquals) {
    pokerGame::context::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_LOW_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS);
    pokerGame::context::BettingContext anotherContext(A_BETTING_ROUND_TYPE, A_HIGH_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS);
    ASSERT_FALSE(bettingContext == anotherContext);
}

}

