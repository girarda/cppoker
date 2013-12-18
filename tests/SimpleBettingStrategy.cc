#include "gtest/gtest.h"
#include "HandMock.h"
#include "playerInterface/bot/SimpleBettingStrategy.h"

using ::testing::Return;

class SimpleBettingStrategy : public ::testing::Test
{
protected:
    pokerGame::Hand* aHand;
    playerInterface::bot::BettingStrategy* simpleBettingStrategy;

    static const float A_BET;
    static const float ZERO_BET;
    static const float BIG_BLIND;

    void initPreFlopPair();
    void initPreFlopSumOfPowerHigherThan16();
    void initPreFlopSumOfPowerLowerThan16();
    void initPostFlopStraight();
    void initPostFlopHighCard();
    void initPostFlopPair();

    virtual void SetUp()
    {
        simpleBettingStrategy = new playerInterface::bot::SimpleBettingStrategy();
        aHand = new pokerGame::Hand();
    }
    virtual void TearDown()
    {
        delete aHand;
        delete simpleBettingStrategy;
    }
};

const float SimpleBettingStrategy::A_BET(10);
const float SimpleBettingStrategy::ZERO_BET(0);
const float SimpleBettingStrategy::BIG_BLIND(1);

TEST_F(SimpleBettingStrategy, whenPreFlopIfHandValueIsAPairMakeDecisionReturnsCall)
{
    initPreFlopPair();
    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).choice;
    ASSERT_EQ(pokerGame::CALL, choice);
}

TEST_F(SimpleBettingStrategy, whenPreFlopIfHandValueIsAPairNewBetEqualsBigBlind)
{
    initPreFlopPair();
    float newBet = simpleBettingStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).bet;
    ASSERT_EQ(BIG_BLIND, newBet);
}

TEST_F(SimpleBettingStrategy, whenPreFlopIfSumOfPowerOfHandIsHigherThan16MakeDecisionReturnsCheck)
{
    initPreFlopSumOfPowerHigherThan16();
    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).choice;
    ASSERT_EQ(pokerGame::CHECK, choice);
}

TEST_F(SimpleBettingStrategy, whenPreFlopIfSumOfPowerOfHandIsHigherThan16NewBetIsZero)
{
    initPreFlopSumOfPowerHigherThan16();
    float newBet = simpleBettingStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).bet;
    ASSERT_EQ(0, newBet);
}

TEST_F(SimpleBettingStrategy, whenPreFlopIfSumOfPowerOfHandIsLowerThan16MakeDecisionReturnsCheck)
{
    initPreFlopSumOfPowerLowerThan16();
    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).choice;
    ASSERT_EQ(pokerGame::FOLD, choice);
}

TEST_F(SimpleBettingStrategy, whenPreFlopIfSumOfPowerOfHandIsLowerThan16NewBetIsZero)
{
    initPreFlopSumOfPowerLowerThan16();
    float newBet = simpleBettingStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).bet;
    ASSERT_EQ(0, newBet);
}

TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsHigherOrEqualsToStraightMakeDecisionReturnsRaise)
{
    initPostFlopStraight();
    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).choice;
    ASSERT_EQ(pokerGame::CALL, choice);
}

TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsHigherOrEqualsToStraightNewBetEqualsBigBlind)
{
    initPostFlopStraight();
    float newBet = simpleBettingStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).bet;
    ASSERT_EQ(BIG_BLIND, newBet);
}

TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsHighCardAndBetIsNotZeroThenFold)
{
    initPostFlopHighCard();
    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).choice;
    ASSERT_EQ(pokerGame::FOLD, choice);
}

TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsHighCardAndBetIsNotZeroThenNewBetIsZero)
{
    initPostFlopHighCard();
    float newBet = simpleBettingStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).bet;
    ASSERT_EQ(0, newBet);
}

TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsHighCardAndBetIsZeroThenCheck)
{
    initPostFlopHighCard();
    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*aHand, ZERO_BET, BIG_BLIND).choice;
    ASSERT_EQ(pokerGame::CHECK, choice);
}

TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsHighCardAndBetIsZeroThenNewBetIsZero)
{
    initPostFlopHighCard();
    float newBet = simpleBettingStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).bet;
    ASSERT_EQ(0, newBet);
}

TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsBetterThanHighCardButLessThanStraifhtThenCheck)
{
    initPostFlopPair();
    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).choice;
    ASSERT_EQ(pokerGame::CHECK, choice);
}

TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsBetterThanHighCardButLessThanStraifhtThenNewBetIsZero)
{
    initPostFlopPair();
    float newBet = simpleBettingStrategy->makeDecision(*aHand, A_BET, BIG_BLIND).bet;
    ASSERT_EQ(0, newBet);
}

void SimpleBettingStrategy::initPreFlopPair()
{
    pokerGame::Card c1(pokerGame::ACE, pokerGame::SPADE);
    pokerGame::Card c2(pokerGame::ACE, pokerGame::HEART);
    aHand->addCard(c1);
    aHand->addCard(c2);
}

void SimpleBettingStrategy::initPreFlopSumOfPowerHigherThan16()
{
    pokerGame::Card c1(pokerGame::KING, pokerGame::SPADE);
    pokerGame::Card c2(pokerGame::QUEEN, pokerGame::HEART);
    aHand->addCard(c1);
    aHand->addCard(c2);
}

void SimpleBettingStrategy::initPreFlopSumOfPowerLowerThan16()
{
    pokerGame::Card c1(2, pokerGame::SPADE);
    pokerGame::Card c2(3, pokerGame::HEART);
    aHand->addCard(c1);
    aHand->addCard(c2);
}

void SimpleBettingStrategy::initPostFlopStraight()
{
    pokerGame::Card c1(2, pokerGame::SPADE);
    pokerGame::Card c2(3, pokerGame::HEART);
    pokerGame::Card c3(4, pokerGame::HEART);
    pokerGame::Card c4(5, pokerGame::HEART);
    pokerGame::Card c5(6, pokerGame::HEART);
    aHand->addCard(c1);
    aHand->addCard(c2);
    aHand->addCard(c3);
    aHand->addCard(c4);
    aHand->addCard(c5);
}

void SimpleBettingStrategy::initPostFlopHighCard()
{
    pokerGame::Card c1(2, pokerGame::SPADE);
    pokerGame::Card c3(3, pokerGame::HEART);
    pokerGame::Card c2(4, pokerGame::HEART);
    aHand->addCard(c1);
    aHand->addCard(c2);
    aHand->addCard(c3);
}

void SimpleBettingStrategy::initPostFlopPair()
{
    pokerGame::Card c1(2, pokerGame::SPADE);
    pokerGame::Card c3(2, pokerGame::HEART);
    pokerGame::Card c2(4, pokerGame::HEART);
    aHand->addCard(c1);
    aHand->addCard(c2);
    aHand->addCard(c3);
}

