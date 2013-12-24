#include "gtest/gtest.h"
#include "pokerGame/context/ActionContext.h"
#include "pokerGame/context/BettingContext.h"
#include "pokerGame/context/HandContext.h"
#include "pokerGame/Decision.h"

namespace tests {

class HandContextTest : public ::testing::Test {
protected:
    static const int A_NUMBER_OF_RAISES;
    static const int A_NUMBER_OF_PLAYERS;
    static const int ANOTHER_NUMBER_OF_PLAYERS;
    static const double HAND_STRENGTH;
    static const float A_BET;
    static const pokerGame::BettingRoundType A_BETTING_ROUND_TYPE;
};

const int HandContextTest::A_NUMBER_OF_RAISES(2);
const int HandContextTest::A_NUMBER_OF_PLAYERS(4);
const int HandContextTest::ANOTHER_NUMBER_OF_PLAYERS(2);
const double HandContextTest::HAND_STRENGTH(1.1);
const float HandContextTest::A_BET(10.0f);
const pokerGame::BettingRoundType HandContextTest::A_BETTING_ROUND_TYPE(pokerGame::PRE_FLOP);


TEST_F(HandContextTest, canGetHandStrength) {
    pokerGame::Decision aDecision = {pokerGame::RAISE, A_BET};
    pokerGame::context::ActionContext actionContext(pokerGame::context::BettingContext(A_BETTING_ROUND_TYPE, A_NUMBER_OF_RAISES, A_NUMBER_OF_PLAYERS), aDecision);
    pokerGame::context::HandContext handContext(actionContext, HAND_STRENGTH);

    double handStrength = handContext.getHandStrength();
    ASSERT_EQ(HAND_STRENGTH, handStrength);
}

TEST_F(HandContextTest, hasSameActionContextReturnsTrueWhenActionContextIsTheSame) {
    pokerGame::Decision aDecision = {pokerGame::RAISE, A_BET};
    pokerGame::context::ActionContext actionContext(pokerGame::context::BettingContext(A_BETTING_ROUND_TYPE, A_NUMBER_OF_RAISES, A_NUMBER_OF_PLAYERS), aDecision);
    pokerGame::context::HandContext handContext(actionContext, HAND_STRENGTH);

    bool hasSameActionContext = handContext.hasSameActionContext(actionContext);
    ASSERT_TRUE(hasSameActionContext);
}

TEST_F(HandContextTest, hasSameActionContextReturnsFalseWhenActionContextIsDifferent) {
    pokerGame::Decision aDecision = {pokerGame::RAISE, A_BET};
    pokerGame::context::ActionContext actionContext(pokerGame::context::BettingContext(A_BETTING_ROUND_TYPE, A_NUMBER_OF_RAISES, A_NUMBER_OF_PLAYERS), aDecision);
    pokerGame::context::ActionContext aDifferentActionContext(pokerGame::context::BettingContext(A_BETTING_ROUND_TYPE, A_NUMBER_OF_RAISES, ANOTHER_NUMBER_OF_PLAYERS), aDecision);
    pokerGame::context::HandContext handContext(actionContext, HAND_STRENGTH);

    bool hasSameActionContext = handContext.hasSameActionContext(actionContext);
    ASSERT_TRUE(hasSameActionContext);
}

}

