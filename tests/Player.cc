#include "gtest/gtest.h"
#include "core/Player.h"
#include "IPlayerMock.cc"
#include "HandMock.cc"

using ::testing::Return;

class PlayerTest : public ::testing::Test
{
    protected:
        test::IPlayerMock* aPlayerImpl;
        test::HandMock* aHand;
        pcore::Player* aPlayer;

        static const float NO_MONEY;
        static const float MONEY_WON;

        virtual void SetUp()
        {
           aPlayerImpl = new test::IPlayerMock;
           aHand = new test::HandMock;
           aPlayer = new pcore::Player(aPlayerImpl, aHand);
        }
        virtual void TearDown()
        {
            delete aPlayer;
            delete aHand;
            delete aPlayerImpl;
        }
};

const float PlayerTest::NO_MONEY(0);
const float PlayerTest::MONEY_WON(5);

TEST_F(PlayerTest, newPlayerIsNotPlaying)
{
    bool playerIsPlaying = aPlayer->isPlaying();

    ASSERT_FALSE(playerIsPlaying);
}

TEST_F(PlayerTest, newPlayerHasNoMoney)
{
    float initialMoney = aPlayer->getMoney();

    ASSERT_EQ(NO_MONEY, initialMoney);
}

TEST_F(PlayerTest, newPlayerHasNoMoneyInPot)
{
    float initialPot = aPlayer->getPot();

    ASSERT_EQ(NO_MONEY, initialPot);
}

TEST_F(PlayerTest, playerIsPlayingAfterStarting)
{
    aPlayer->startPlaying();

    bool playerIsPlaying = aPlayer->isPlaying();

    ASSERT_TRUE(playerIsPlaying);
}

TEST_F(PlayerTest, playerIsNotFoldedAfterSetupingANewTableTurn)
{
    aPlayer->startPlaying();
    aPlayer->setupForNewTableTurn();

    bool playerIsFolded = aPlayer->isFolded();

    ASSERT_FALSE(playerIsFolded);
}

TEST_F(PlayerTest, playerIsFoldedWhenFoldingAfterSetupingAnewTableTurn)
{
    aPlayer->startPlaying();
    aPlayer->setupForNewTableTurn();
    aPlayer->fold();

    bool playerIsFolded = aPlayer->isFolded();

    ASSERT_TRUE(playerIsFolded);
}

TEST_F(PlayerTest, playerPotIsClearedWhenSettingForNewTableTurn)
{
    aPlayer->setMoney(5);
    aPlayer->startPlaying();
    aPlayer->addToPot(5);
    aPlayer->setupForNewTableTurn();

    float moneyInPot = aPlayer->getPot();

    ASSERT_EQ(PlayerTest::NO_MONEY, moneyInPot);
}

TEST_F(PlayerTest, playerHasMoreMoneyWhenWinningMoney)
{
    aPlayer->winMoney(PlayerTest::MONEY_WON);

    float playersMoney = aPlayer->getMoney();

    ASSERT_EQ(PlayerTest::MONEY_WON, playersMoney);
}

TEST_F(PlayerTest, makingDecisionReturnsCheckWhenPlayerChecks)
{
    pcore::Decision aDecision = {pcore::CHECK, 0};
    EXPECT_CALL(*aPlayerImpl, makeDecision(0)).Times(1).WillOnce(Return(aDecision));

    pcore::Decision returnedDecision = aPlayer->makeDecision((0));
    
    ASSERT_EQ(aDecision.choice, returnedDecision.choice);
    ASSERT_EQ(aDecision.bet, returnedDecision.bet);
}

TEST_F(PlayerTest, makingDecisionAsksUserASecondTimesIfItDoesNotHaveEnoughMoneyForHisDecision)
{
    pcore::Decision callDecision = {pcore::CALL, 5};
    pcore::Decision checkDecision = {pcore::CHECK, 0};
    EXPECT_CALL(*aPlayerImpl, makeDecision(0)).Times(2).WillOnce(Return(callDecision)).WillOnce(Return(checkDecision));

    pcore::Decision returnedDecision = aPlayer->makeDecision((0));
    
    ASSERT_EQ(checkDecision.choice, returnedDecision.choice);
    ASSERT_EQ(checkDecision.bet, returnedDecision.bet);
}

TEST_F(PlayerTest, makingDecisionReturnsCallWhenPlayerCallsAndHasEnoughMoney)
{
    aPlayer->setMoney(5);
    pcore::Decision callDecision = {pcore::CALL, 5};
    EXPECT_CALL(*aPlayerImpl, makeDecision(0)).Times(1).WillOnce(Return(callDecision));

    pcore::Decision returnedDecision = aPlayer->makeDecision((0));
    
    ASSERT_EQ(callDecision.choice, returnedDecision.choice);
    ASSERT_EQ(callDecision.bet, returnedDecision.bet);
}

TEST_F(PlayerTest, playerFoldsWhenDecisionIsToFold)
{
    pcore::Decision foldDecision = {pcore::FOLD, 0};
    EXPECT_CALL(*aPlayerImpl, makeDecision(0)).Times(1).WillOnce(Return(foldDecision));

    pcore::Decision returnedDecision = aPlayer->makeDecision((0));
    bool playerFolded = aPlayer->isFolded();
    
    ASSERT_EQ(foldDecision.choice, returnedDecision.choice);
    ASSERT_EQ(foldDecision.bet, returnedDecision.bet);
    ASSERT_TRUE(playerFolded);
}
