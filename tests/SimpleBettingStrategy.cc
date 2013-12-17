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
    static const float INITIAL_AMOUNT_MONEY;
    static const float TOO_MUCH_MONEY;

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

TEST_F(SimpleBettingStrategy, whenPreFlopIfHandValueIsAPairMakeDecisionReturnsCall)
{
    pokerGame::Card c1(pokerGame::ACE, pokerGame::SPADE);
    pokerGame::Card c2(pokerGame::ACE, pokerGame::HEART);
    aHand->addCard(c1);
    aHand->addCard(c2);

    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*aHand, A_BET).choice;

    ASSERT_EQ(pokerGame::CALL, choice);
}

TEST_F(SimpleBettingStrategy, whenPreFlopIfSumOfPowerOfHandIsHigherThan16MakeDecisionReturnsCheck)
{
    pokerGame::Card c1(pokerGame::KING, pokerGame::SPADE);
    pokerGame::Card c2(pokerGame::QUEEN, pokerGame::HEART);
    aHand->addCard(c1);
    aHand->addCard(c2);

    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*aHand, A_BET).choice;

    ASSERT_EQ(pokerGame::CHECK, choice);
}

TEST_F(SimpleBettingStrategy, whenPreFlopIfSumOfPowerOfHandIsLowerThan16MakeDecisionReturnsCheck)
{
    pokerGame::Card c1(2, pokerGame::SPADE);
    pokerGame::Card c2(3, pokerGame::HEART);

    aHand->addCard(c1);
    aHand->addCard(c2);
    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*aHand, A_BET).choice;

    ASSERT_EQ(pokerGame::FOLD, choice);
}

TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsHigherOrEqualsToStraigthMakeDecisionReturnsRaise)
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
    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*aHand, A_BET).choice;

    ASSERT_EQ(pokerGame::CALL, choice);
}

TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsHighCardAndBetIsNotZeroThenFold)
{
    pokerGame::Card c1(2, pokerGame::SPADE);
    pokerGame::Card c3(3, pokerGame::HEART);
    pokerGame::Card c2(4, pokerGame::HEART);


    aHand->addCard(c1);
    aHand->addCard(c2);
    aHand->addCard(c3);

    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*aHand, A_BET).choice;

    ASSERT_EQ(pokerGame::FOLD, choice);
}

TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsHighCardAndBetIsZeroThenCheck)
{
    pokerGame::Card c1(2, pokerGame::SPADE);
    pokerGame::Card c3(3, pokerGame::HEART);
    pokerGame::Card c2(4, pokerGame::HEART);


    aHand->addCard(c1);
    aHand->addCard(c2);
    aHand->addCard(c3);

    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*aHand, ZERO_BET).choice;

    ASSERT_EQ(pokerGame::CHECK, choice);
}

TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsBetterThanHighCardButLessThanStraifhtThenCheck)
{
    pokerGame::Card c1(2, pokerGame::SPADE);
    pokerGame::Card c3(2, pokerGame::HEART);
    pokerGame::Card c2(4, pokerGame::HEART);


    aHand->addCard(c1);
    aHand->addCard(c2);
    aHand->addCard(c3);

    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*aHand, A_BET).choice;

    ASSERT_EQ(pokerGame::CHECK, choice);
}
