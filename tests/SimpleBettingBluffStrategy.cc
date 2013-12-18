#include "gtest/gtest.h"
#include "HandMock.h"
#include "playerInterface/bot/SimpleBettingBluffStrategy.h"

using ::testing::Return;

class SimpleBettingBluffStrategyTest : public ::testing::Test
{
protected:
    pokerGame::Hand* aHand;
    playerInterface::bot::BettingStrategy* simpleBettingBluffStrategy;

    static const float A_BET;
    static const float ZERO_BET;
    static const float BIG_BLIND;

    void initPreFlopPair();
    void initPreFlopSumOfPowerHigherThan16();
    void initPreFlopSumOfPowerLowerThan16HigherThan8();
    void initPreFlopSumOfPowerLower8();
    void initPostFlopThreeOfAKind();
    void initPostFlopHighCard();
    void initPostFlopPair();

    virtual void SetUp()
    {
        simpleBettingBluffStrategy = new playerInterface::bot::SimpleBettingBluffStrategy();
        aHand = new pokerGame::Hand();
    }
    virtual void TearDown()
    {
        delete aHand;
        delete simpleBettingBluffStrategy;
    }
};

const float SimpleBettingBluffStrategyTest::A_BET(10);
const float SimpleBettingBluffStrategyTest::ZERO_BET(0);
const float SimpleBettingBluffStrategyTest::BIG_BLIND(1);

TEST_F(SimpleBettingBluffStrategyTest, whenPreFlopIfHandValueIsAPairMakeDecisionReturnsCall)
{
    initPreFlopPair();
    pokerGame::Choice choice = simpleBettingBluffStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).choice;
    ASSERT_EQ(pokerGame::CALL, choice);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPreFlopIfHandValueIsAPairNewBetEqualsBigBlind)
{
    initPreFlopPair();
    float newBet = simpleBettingBluffStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).bet;
    ASSERT_EQ(BIG_BLIND, newBet);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPreFlopIfSumOfPowerOfHandIsLowerThan9ThenBluffAndRaise)
{
    initPreFlopSumOfPowerLower8();
    pokerGame::Choice choice = simpleBettingBluffStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).choice;
    ASSERT_EQ(pokerGame::CALL, choice);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPreFlopIfHandValueIsLowerThan9ThenNewBetEqualsBigBlind)
{
    initPreFlopSumOfPowerLower8();
    float newBet = simpleBettingBluffStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).bet;
    ASSERT_EQ(BIG_BLIND, newBet);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPreFlopIfSumOfPowerOfHandIsHigherThan16MakeDecisionReturnsCheck)
{
    initPreFlopSumOfPowerHigherThan16();
    pokerGame::Choice choice = simpleBettingBluffStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).choice;
    ASSERT_EQ(pokerGame::CHECK, choice);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPreFlopIfSumOfPowerOfHandIsHigherThan16NewBetIsZero)
{
    initPreFlopSumOfPowerHigherThan16();
    float newBet = simpleBettingBluffStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).bet;
    ASSERT_EQ(0, newBet);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPreFlopIfSumOfPowerOfHandIsLowerThan16MakeDecisionReturnsCheck)
{
    initPreFlopSumOfPowerLowerThan16HigherThan8();
    pokerGame::Choice choice = simpleBettingBluffStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).choice;
    ASSERT_EQ(pokerGame::FOLD, choice);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPreFlopIfSumOfPowerOfHandIsLowerThan16NewBetIsZero)
{
    initPreFlopSumOfPowerLowerThan16HigherThan8();
    float newBet = simpleBettingBluffStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).bet;
    ASSERT_EQ(0, newBet);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPostFlopIfHandValueIsHigherOrEqualsToThreeOfAKindMakeDecisionReturnsRaise)
{
    initPostFlopThreeOfAKind();
    pokerGame::Choice choice = simpleBettingBluffStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).choice;
    ASSERT_EQ(pokerGame::CALL, choice);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPostFlopIfHandValueIsHigherOrEqualsToThreeOfAKindNewBetEqualsBigBlind)
{
    initPostFlopThreeOfAKind();
    float newBet = simpleBettingBluffStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).bet;
    ASSERT_EQ(BIG_BLIND, newBet);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPostFlopIfHandValueIsHighCardBluffAndRaise)
{
    initPostFlopHighCard();
    pokerGame::Choice choice = simpleBettingBluffStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).choice;
    ASSERT_EQ(pokerGame::CALL, choice);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPostFlopIfHandValueIsHighCardAndBetIsNotZeroThenNewBetEqualsBigBlind)
{
    initPostFlopHighCard();
    float newBet = simpleBettingBluffStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).bet;
    ASSERT_EQ(BIG_BLIND, newBet);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPostFlopIfHandValueIsLowerThanThreeOfAKindAndBetIsZeroThenCheck)
{
    initPostFlopPair();
    pokerGame::Choice choice = simpleBettingBluffStrategy->makeDecision(*aHand, ZERO_BET, BIG_BLIND).choice;
    ASSERT_EQ(pokerGame::CHECK, choice);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPostFlopIfHandValueIsLowerThanThreeOfAKindAndBetIsZeroThenNewBetIsZero)
{
    initPostFlopPair();
    float newBet = simpleBettingBluffStrategy->makeDecision(*aHand, ZERO_BET, BIG_BLIND).bet;
    ASSERT_EQ(0, newBet);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPostFlopIfHandValueIsLowerThanThreeOfAKindAndBetIsNotZeroThenFold)
{
    initPostFlopPair();
    pokerGame::Choice choice = simpleBettingBluffStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).choice;
    ASSERT_EQ(pokerGame::FOLD, choice);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPostFlopIfHandValueIsLowerThanThreeOfAKindAndBetIsNotZeroThenNewBetIsZero)
{
    initPostFlopPair();
    float newBet = simpleBettingBluffStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).bet;
    ASSERT_EQ(0, newBet);
}

void SimpleBettingBluffStrategyTest::initPreFlopPair()
{
    pokerGame::Card c1(pokerGame::ACE, pokerGame::SPADE);
    pokerGame::Card c2(pokerGame::ACE, pokerGame::HEART);
    aHand->addCard(c1);
    aHand->addCard(c2);
}

void SimpleBettingBluffStrategyTest::initPreFlopSumOfPowerHigherThan16()
{
    pokerGame::Card c1(pokerGame::KING, pokerGame::SPADE);
    pokerGame::Card c2(pokerGame::QUEEN, pokerGame::HEART);
    aHand->addCard(c1);
    aHand->addCard(c2);
}

void SimpleBettingBluffStrategyTest::initPreFlopSumOfPowerLowerThan16HigherThan8()
{
    pokerGame::Card c1(2, pokerGame::SPADE);
    pokerGame::Card c2(8, pokerGame::HEART);
    aHand->addCard(c1);
    aHand->addCard(c2);
}

void SimpleBettingBluffStrategyTest::initPreFlopSumOfPowerLower8()
{
    pokerGame::Card c1(2, pokerGame::SPADE);
    pokerGame::Card c2(3, pokerGame::HEART);
    aHand->addCard(c1);
    aHand->addCard(c2);
}


void SimpleBettingBluffStrategyTest::initPostFlopThreeOfAKind()
{
    pokerGame::Card c1(2, pokerGame::SPADE);
    pokerGame::Card c2(3, pokerGame::HEART);
    pokerGame::Card c3(3, pokerGame::SPADE);
    pokerGame::Card c4(3, pokerGame::CLUB);
    pokerGame::Card c5(6, pokerGame::HEART);
    aHand->addCard(c1);
    aHand->addCard(c2);
    aHand->addCard(c3);
    aHand->addCard(c4);
    aHand->addCard(c5);
}

void SimpleBettingBluffStrategyTest::initPostFlopHighCard()
{
    pokerGame::Card c1(2, pokerGame::SPADE);
    pokerGame::Card c3(3, pokerGame::HEART);
    pokerGame::Card c2(4, pokerGame::HEART);
    aHand->addCard(c1);
    aHand->addCard(c2);
    aHand->addCard(c3);
}

void SimpleBettingBluffStrategyTest::initPostFlopPair()
{
    pokerGame::Card c1(2, pokerGame::SPADE);
    pokerGame::Card c3(2, pokerGame::HEART);
    pokerGame::Card c2(4, pokerGame::HEART);
    aHand->addCard(c1);
    aHand->addCard(c2);
    aHand->addCard(c3);
}

