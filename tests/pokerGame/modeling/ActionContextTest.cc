#include "gtest/gtest.h"
#include "pokerGame/modeling/ActionContext.h"
#include "pokerGame/modeling/BettingContext.h"
#include "pokerGame/Decision.h"

namespace tests {

class ActionContextTest : public ::testing::Test {
protected:
    static const int A_LOW_NUMBER_OF_RAISES;
    static const int A_HIGH_NUMBER_OF_RAISES;
    static const int A_LOW_NUMBER_OF_PLAYERS;
    static const int A_HIGH_NUMBER_OF_PLAYERS;
    static const pokerGame::BettingRoundType A_BETTING_ROUND_TYPE;
};

const int ActionContextTest::A_LOW_NUMBER_OF_RAISES(2);
const int ActionContextTest::A_HIGH_NUMBER_OF_RAISES(4);
const int ActionContextTest::A_LOW_NUMBER_OF_PLAYERS(2);
const int ActionContextTest::A_HIGH_NUMBER_OF_PLAYERS(4);
const pokerGame::BettingRoundType ActionContextTest::A_BETTING_ROUND_TYPE(pokerGame::PRE_FLOP);


TEST_F(ActionContextTest, twoActionContextsAreEqualsIfTheirActionChoiceIsTheSameAndTheirBettingContextsAreTheSame) {
    pokerGame::modeling::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_LOW_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS);
    pokerGame::Decision aDecision = {pokerGame::CALL, 0};

    pokerGame::modeling::ActionContext anActionContext(bettingContext, aDecision);
    pokerGame::modeling::ActionContext anotherActionContext(bettingContext, aDecision);

    ASSERT_EQ(anActionContext, anotherActionContext);
}

TEST_F(ActionContextTest, twoActionContextsAreDifferentIfTheirBettingContextAreDifferent) {
    pokerGame::modeling::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_LOW_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS);
    pokerGame::modeling::BettingContext anotherBettingContext(A_BETTING_ROUND_TYPE, A_LOW_NUMBER_OF_RAISES, A_LOW_NUMBER_OF_PLAYERS);
    pokerGame::Decision aDecision = {pokerGame::CALL, 0};

    pokerGame::modeling::ActionContext anActionContext(bettingContext, aDecision);
    pokerGame::modeling::ActionContext anotherActionContext(anotherBettingContext, aDecision);

    ASSERT_FALSE(anActionContext == anotherActionContext);
}

TEST_F(ActionContextTest, twoActionContextsAreDifferentIfTheirDecisionAreNotTheSame) {
    pokerGame::modeling::BettingContext bettingContext(A_BETTING_ROUND_TYPE, A_LOW_NUMBER_OF_RAISES, A_HIGH_NUMBER_OF_PLAYERS);
    pokerGame::Decision aDecision = {pokerGame::CALL, 0};
    pokerGame::Decision anotherDecision = {pokerGame::FOLD, 0};

    pokerGame::modeling::ActionContext anActionContext(bettingContext, aDecision);
    pokerGame::modeling::ActionContext anotherActionContext(bettingContext, anotherDecision);

    ASSERT_FALSE(anActionContext == anotherActionContext);
}

}

