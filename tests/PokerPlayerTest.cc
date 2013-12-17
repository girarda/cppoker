#include "gtest/gtest.h"
#include "pokerGame/PokerPlayer.h"
#include "PlayerControllerMock.h"
#include "HandMock.h"
#include "pokerGame/PlayerController.h"

using ::testing::Return;

class PlayerTest : public ::testing::Test
{
protected:
    test::PlayerControllerMock* aPlayerController;
    test::HandMock* aHand;
    pokerGame::PokerPlayer* aPlayer;

    static const float NO_MONEY;
    static const float MONEY_WON;
    static const float INITIAL_AMOUNT_MONEY;
    static const float TOO_MUCH_MONEY;

    virtual void SetUp()
    {
        aPlayerController = new test::PlayerControllerMock();
        aHand = new test::HandMock();
        aPlayer = new pokerGame::PokerPlayer(aPlayerController, INITIAL_AMOUNT_MONEY);
    }
    virtual void TearDown()
    {
        delete aPlayer;
        delete aHand;
    }
};

const float PlayerTest::NO_MONEY(0);
const float PlayerTest::MONEY_WON(10);
const float PlayerTest::INITIAL_AMOUNT_MONEY(5);
const float PlayerTest::TOO_MUCH_MONEY(10);

TEST_F(PlayerTest, newPlayerIsNotPlaying)
{
    bool playerIsPlaying = aPlayer->isPlaying();

    ASSERT_FALSE(playerIsPlaying);
}

TEST_F(PlayerTest, newPlayerHasInitialAmountOfMoney)
{
    float initialMoney = aPlayer->getMoney();

    ASSERT_EQ(INITIAL_AMOUNT_MONEY, initialMoney);
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
    aPlayer->startPlaying();
    aPlayer->addToPot(INITIAL_AMOUNT_MONEY);
    aPlayer->setupForNewTableTurn();

    float moneyInPot = aPlayer->getPot();

    ASSERT_EQ(PlayerTest::NO_MONEY, moneyInPot);
}

TEST_F(PlayerTest, playerHasMoreMoneyWhenWinningMoney)
{
    aPlayer->winMoney(PlayerTest::MONEY_WON);

    float playersMoney = aPlayer->getMoney();

    ASSERT_EQ(PlayerTest::MONEY_WON + PlayerTest::INITIAL_AMOUNT_MONEY, playersMoney);
}

TEST_F(PlayerTest, makingDecisionReturnsCheckWhenPlayerChecks)
{
    pokerGame::Decision aDecision = {pokerGame::CHECK, 0};
    EXPECT_CALL(*aPlayerController, makeDecision(*aHand, 0)).Times(1).WillOnce(Return(aDecision));

    pokerGame::Decision returnedDecision = aPlayer->makeDecision(0);

    ASSERT_EQ(aDecision.choice, returnedDecision.choice);
    ASSERT_EQ(aDecision.bet, returnedDecision.bet);
}

TEST_F(PlayerTest, makingDecisionAsksUserASecondTimesIfItDoesNotHaveEnoughMoneyForHisDecision)
{
    pokerGame::Decision callDecision = {pokerGame::CALL, TOO_MUCH_MONEY};
    pokerGame::Decision checkDecision = {pokerGame::CHECK, 0};
    EXPECT_CALL(*aPlayerController, makeDecision(*aHand, 0)).Times(2).WillOnce(Return(callDecision)).WillOnce(Return(checkDecision));

    pokerGame::Decision returnedDecision = aPlayer->makeDecision((0));

    ASSERT_EQ(checkDecision.choice, returnedDecision.choice);
    ASSERT_EQ(checkDecision.bet, returnedDecision.bet);
}

TEST_F(PlayerTest, makingDecisionReturnsCallWhenPlayerCallsAndHasEnoughMoney)
{
    aPlayer->setMoney(5);
    pokerGame::Decision callDecision = {pokerGame::CALL, 5};
    EXPECT_CALL(*aPlayerController, makeDecision(*aHand, 0)).Times(1).WillOnce(Return(callDecision)); 
    pokerGame::Decision returnedDecision = aPlayer->makeDecision((0));

    ASSERT_EQ(callDecision.choice, returnedDecision.choice);
    ASSERT_EQ(callDecision.bet, returnedDecision.bet);
}

TEST_F(PlayerTest, playerFoldsWhenDecisionIsToFold)
{
    pokerGame::Decision foldDecision = {pokerGame::FOLD, 0};
    EXPECT_CALL(*aPlayerController, makeDecision(*aHand, 0)).Times(1).WillOnce(Return(foldDecision));

    pokerGame::Decision returnedDecision = aPlayer->makeDecision((0));
    bool playerFolded = aPlayer->isFolded();

    ASSERT_EQ(foldDecision.choice, returnedDecision.choice);
    ASSERT_EQ(foldDecision.bet, returnedDecision.bet);
    ASSERT_TRUE(playerFolded);
}
