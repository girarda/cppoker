#include "gtest/gtest.h"
#include "pokerGame/modeling/BettingContext.h"
#include "pokerGame/BettingRoundType.h"

namespace tests {

class BettingContextTest : public ::testing::Test {
protected:
    static const int A_LOW_NUMBER_OF_RAISES;
    static const int A_HIGH_NUMBER_OF_RAISES;
    static const int A_LOW_NUMBER_OF_PLAYERS;
    static const int A_HIGH_NUMBER_OF_PLAYERS;
    static const float MIN_BET;
    static const float BIG_BLIND;
    static const pokerGame::BettingRoundType A_BETTING_ROUND_TYPE;
};

const int BettingContextTest::A_LOW_NUMBER_OF_RAISES(2);
const int BettingContextTest::A_HIGH_NUMBER_OF_RAISES(4);
const int BettingContextTest::A_LOW_NUMBER_OF_PLAYERS(2);
const int BettingContextTest::A_HIGH_NUMBER_OF_PLAYERS(4);
const float BettingContextTest::MIN_BET(2);
const float BettingContextTest::BIG_BLIND(2);
const pokerGame::BettingRoundType BettingContextTest::A_BETTING_ROUND_TYPE(pokerGame::PRE_FLOP);


TEST_F(BettingContextTest, bettingContextDoesNotHaveManyRaisesIfNumbeOfRaisesIsLowerThan2) {
    pokerGame::modeling::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_LOW_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS, MIN_BET, BIG_BLIND);
    bool hasManyRaises = bettingContext.hasManyRaises();
    ASSERT_FALSE(hasManyRaises);
}

TEST_F(BettingContextTest, bettingContextHasManyRaisesIfNumbeOfRaisesIsHigherThan2) {
    pokerGame::modeling::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_HIGH_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS, MIN_BET, BIG_BLIND);
    bool hasManyRaises = bettingContext.hasManyRaises();
    ASSERT_TRUE(hasManyRaises);
}

TEST_F(BettingContextTest, bettingContextDoesNotHaveManyPlayersIfNumbeOfPlayersIsLowerThan2) {
    pokerGame::modeling::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_LOW_NUMBER_OF_RAISES, A_LOW_NUMBER_OF_PLAYERS, MIN_BET, BIG_BLIND);
    bool hasManyPlayers = bettingContext.hasManyPlayers();
    ASSERT_FALSE(hasManyPlayers);
}

TEST_F(BettingContextTest, bettingContextHasManyPlayersIfNumbeOfPlayersIsHigherThan3) {
    pokerGame::modeling::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_HIGH_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS, MIN_BET, BIG_BLIND);
    bool hasManyPlayers = bettingContext.hasManyPlayers();
    ASSERT_TRUE(hasManyPlayers);
}

TEST_F(BettingContextTest, canGetBettingRoundType) {
    pokerGame::modeling::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_LOW_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS, MIN_BET, BIG_BLIND);
    pokerGame::BettingRoundType returnedBettingType = bettingContext.getBettingRoundType();
    ASSERT_EQ(A_BETTING_ROUND_TYPE, returnedBettingType);
}

TEST_F(BettingContextTest, canGetNumberOfRaises) {
    pokerGame::modeling::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_LOW_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS, MIN_BET, BIG_BLIND);
    int numberOfRaises = bettingContext.getNumberOfRaises();
    ASSERT_EQ(A_LOW_NUMBER_OF_RAISES, numberOfRaises);
}

TEST_F(BettingContextTest, canGetNumberOfPlayers) {
    pokerGame::modeling::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_LOW_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS, MIN_BET, BIG_BLIND);
    int numberOfPlayers = bettingContext.getNumberOfPlayers();
    ASSERT_EQ(A_HIGH_NUMBER_OF_PLAYERS, numberOfPlayers);
}

TEST_F(BettingContextTest, canGetMinBet) {
    pokerGame::modeling::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_LOW_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS, MIN_BET, BIG_BLIND);
    float minBet = bettingContext.getMinBet();
    ASSERT_EQ(MIN_BET, minBet);
}

TEST_F(BettingContextTest, canGetBigBlind) {
    pokerGame::modeling::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_LOW_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS, MIN_BET, BIG_BLIND);
    float bigBlind = bettingContext.getBigBlind();
    ASSERT_EQ(BIG_BLIND, bigBlind);
}

TEST_F(BettingContextTest, twoBettingContextsAreEqualsIfEveryMembersAreQeuals) {
    pokerGame::modeling::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_LOW_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS, MIN_BET, BIG_BLIND);
    pokerGame::modeling::BettingContext anotherContext(A_BETTING_ROUND_TYPE, A_LOW_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS, MIN_BET, BIG_BLIND);
    ASSERT_EQ(bettingContext, anotherContext);
}

TEST_F(BettingContextTest, twoBettingContextsAreNotEqualsIfEveryMembersAreNotEquals) {
    pokerGame::modeling::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_LOW_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS, MIN_BET, BIG_BLIND);
    pokerGame::modeling::BettingContext anotherContext(A_BETTING_ROUND_TYPE, A_HIGH_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS, MIN_BET, BIG_BLIND);
    ASSERT_FALSE(bettingContext == anotherContext);
}

}

