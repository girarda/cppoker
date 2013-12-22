#include "gtest/gtest.h"
#include "pokerGame/PokerPlayer.h"
#include "PlayerControllerMock.h"
#include "pokerGame/PlayerController.h"

using ::testing::Return;
using ::testing::_;

class PlayerTest : public ::testing::Test
{
protected:
    test::PlayerControllerMock* aPlayerController;
    pokerGame::PokerPlayer* aPlayer;

    std::vector<pokerGame::Card>* sharedCards;

    static const float NO_MONEY;
    static const float MONEY_WON;
    static const float INITIAL_AMOUNT_MONEY;
    static const float TOO_MUCH_MONEY;
    static const float BIG_BLIND;
    static const int NUMBER_OF_RAISES;
    static const int NUMBER_OF_PLAYERS;

    virtual void SetUp()
    {
        aPlayerController = new test::PlayerControllerMock();
        sharedCards = new std::vector<pokerGame::Card>();
        aPlayer = new pokerGame::PokerPlayer(aPlayerController, INITIAL_AMOUNT_MONEY);
    }
    virtual void TearDown()
    {
        delete aPlayer;
        delete sharedCards;
    }
};

const float PlayerTest::NO_MONEY(0);
const float PlayerTest::MONEY_WON(10);
const float PlayerTest::INITIAL_AMOUNT_MONEY(5);
const float PlayerTest::TOO_MUCH_MONEY(10);
const float PlayerTest::BIG_BLIND(1);
const int PlayerTest::NUMBER_OF_RAISES(0);
const int PlayerTest::NUMBER_OF_PLAYERS(2);

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
    aPlayer->setupForNewRound();

    bool playerIsFolded = aPlayer->isFolded();

    ASSERT_FALSE(playerIsFolded);
}

TEST_F(PlayerTest, playerIsFoldedWhenFoldingAfterSetupingAnewTableTurn)
{
    aPlayer->startPlaying();
    aPlayer->setupForNewRound();
    aPlayer->fold();

    bool playerIsFolded = aPlayer->isFolded();

    ASSERT_TRUE(playerIsFolded);
}

TEST_F(PlayerTest, playerPotIsClearedWhenSettingForNewTableTurn)
{
    aPlayer->startPlaying();
    aPlayer->addToPot(INITIAL_AMOUNT_MONEY);
    aPlayer->setupForNewRound();

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
    EXPECT_CALL(*aPlayerController, makeDecision(_, *sharedCards, 0, BIG_BLIND, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS)).Times(1).WillOnce(Return(aDecision)); // TODO: _ should be player->hole

    pokerGame::Decision returnedDecision = aPlayer->makeDecision(0, BIG_BLIND, *sharedCards, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS);

    ASSERT_EQ(aDecision.choice, returnedDecision.choice);
    ASSERT_EQ(aDecision.bet, returnedDecision.bet);
}

TEST_F(PlayerTest, makingDecisionAsksUserASecondTimesIfItDoesNotHaveEnoughMoneyForHisDecision)
{
    pokerGame::Decision callDecision = {pokerGame::CALL, TOO_MUCH_MONEY};
    pokerGame::Decision checkDecision = {pokerGame::CHECK, 0};
    EXPECT_CALL(*aPlayerController, makeDecision(_, *sharedCards, 0, BIG_BLIND, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS)).Times(2).WillOnce(Return(callDecision)).WillOnce(Return(checkDecision)); // TODO: _ should be player->hole

    pokerGame::Decision returnedDecision = aPlayer->makeDecision(0, BIG_BLIND, *sharedCards, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS);

    ASSERT_EQ(checkDecision.choice, returnedDecision.choice);
    ASSERT_EQ(checkDecision.bet, returnedDecision.bet);
}

TEST_F(PlayerTest, makingDecisionReturnsCallWhenPlayerCallsAndHasEnoughMoney)
{
    aPlayer->setMoney(5);
    pokerGame::Decision callDecision = {pokerGame::CALL, 5};
    EXPECT_CALL(*aPlayerController, makeDecision(_, *sharedCards, 0, BIG_BLIND, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS)).Times(1).WillOnce(Return(callDecision)); // TODO: _ should be player->hole
    pokerGame::Decision returnedDecision = aPlayer->makeDecision(0, BIG_BLIND, *sharedCards, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS);

    ASSERT_EQ(callDecision.choice, returnedDecision.choice);
    ASSERT_EQ(callDecision.bet, returnedDecision.bet);
}

TEST_F(PlayerTest, playerFoldsWhenDecisionIsToFold)
{
    pokerGame::Decision foldDecision = {pokerGame::FOLD, 0};
    EXPECT_CALL(*aPlayerController, makeDecision(_, *sharedCards, 0, BIG_BLIND, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS)).Times(1).WillOnce(Return(foldDecision)); // TODO: _ should be player->hole

    pokerGame::Decision returnedDecision = aPlayer->makeDecision(0, BIG_BLIND, *sharedCards, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS);
    bool playerFolded = aPlayer->isFolded();

    ASSERT_EQ(foldDecision.choice, returnedDecision.choice);
    ASSERT_EQ(foldDecision.bet, returnedDecision.bet);
    ASSERT_TRUE(playerFolded);
}
