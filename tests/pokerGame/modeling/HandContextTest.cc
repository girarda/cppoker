#include "gtest/gtest.h"
#include "pokerGame/modeling/ActionContext.h"
#include "pokerGame/modeling/BettingContext.h"
#include "pokerGame/modeling/HandContext.h"
#include "pokerGame/Decision.h"

namespace tests {

class HandContextTest : public ::testing::Test {
protected:
    static const int A_NUMBER_OF_RAISES;
    static const int A_NUMBER_OF_PLAYERS;
    static const int ANOTHER_NUMBER_OF_PLAYERS;
    static const double HAND_STRENGTH;
    static const float A_BET;
    static const float MIN_BET;
    static const float BIG_BLIND;
    static const pokerGame::BettingRoundType A_BETTING_ROUND_TYPE;
};

const int HandContextTest::A_NUMBER_OF_RAISES(2);
const int HandContextTest::A_NUMBER_OF_PLAYERS(4);
const int HandContextTest::ANOTHER_NUMBER_OF_PLAYERS(2);
const double HandContextTest::HAND_STRENGTH(1.1);
const float HandContextTest::A_BET(10.0f);
const float HandContextTest::MIN_BET(2);
const float HandContextTest::BIG_BLIND(2);
const pokerGame::BettingRoundType HandContextTest::A_BETTING_ROUND_TYPE(pokerGame::PRE_FLOP);


TEST_F(HandContextTest, canGetHandStrength) {
    pokerGame::Decision aDecision = {pokerGame::RAISE, A_BET};
    pokerGame::modeling::ActionContext actionContext(pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, A_NUMBER_OF_RAISES, A_NUMBER_OF_PLAYERS, MIN_BET, BIG_BLIND), aDecision);
    pokerGame::modeling::HandContext handContext(actionContext, HAND_STRENGTH);

    double handStrength = handContext.getHandStrength();
    ASSERT_EQ(HAND_STRENGTH, handStrength);
}

TEST_F(HandContextTest, hasSameActionContextReturnsTrueWhenActionContextIsTheSame) {
    pokerGame::Decision aDecision = {pokerGame::RAISE, A_BET};
    pokerGame::modeling::ActionContext actionContext(pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, A_NUMBER_OF_RAISES, A_NUMBER_OF_PLAYERS, MIN_BET, BIG_BLIND), aDecision);
    pokerGame::modeling::HandContext handContext(actionContext, HAND_STRENGTH);

    bool hasSameActionContext = handContext.hasSameActionContext(actionContext);
    ASSERT_TRUE(hasSameActionContext);
}

TEST_F(HandContextTest, hasSameActionContextReturnsFalseWhenActionContextIsDifferent) {
    pokerGame::Decision aDecision = {pokerGame::RAISE, A_BET};
    pokerGame::modeling::ActionContext actionContext(pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, A_NUMBER_OF_RAISES, A_NUMBER_OF_PLAYERS, MIN_BET, BIG_BLIND), aDecision);
    pokerGame::modeling::ActionContext aDifferentActionContext(pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, A_NUMBER_OF_RAISES, ANOTHER_NUMBER_OF_PLAYERS, MIN_BET, BIG_BLIND), aDecision);
    pokerGame::modeling::HandContext handContext(actionContext, HAND_STRENGTH);

    bool hasSameActionContext = handContext.hasSameActionContext(actionContext);
    ASSERT_TRUE(hasSameActionContext);
}

}

