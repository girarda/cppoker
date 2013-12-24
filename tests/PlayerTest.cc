#include "gtest/gtest.h"
#include "pokerGame/Player.h"
#include "PlayerControllerMock.h"
#include "pokerGame/PlayerController.h"
#include "pokerGame/BettingContext.h"

using ::testing::Return;
using ::testing::_;

class PlayerTest : public ::testing::Test {
protected:
    test::PlayerControllerMock* aPlayerController;
    pokerGame::Player* aPlayer;
    pokerGame::BettingContext* bettingContext;
    std::vector<pokerGame::Card>* sharedCards;

    static const float NO_MONEY;
    static const float MONEY_WON;
    static const float INITIAL_AMOUNT_MONEY;
    static const float TOO_MUCH_MONEY;
    static const float BIG_BLIND;
    static const int NUMBER_OF_RAISES;
    static const int NUMBER_OF_PLAYERS;
    static const pokerGame::BettingRoundType A_BETTING_ROUND_TYPE;

    virtual void SetUp() {
        aPlayerController = new test::PlayerControllerMock();
        sharedCards = new std::vector<pokerGame::Card>();
        aPlayer = new pokerGame::Player(aPlayerController, INITIAL_AMOUNT_MONEY);
        aPlayer->startPlaying();
        bettingContext = new pokerGame::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS);
    }
    virtual void TearDown() {
        delete aPlayer;
        delete sharedCards;
        delete bettingContext;
    }
};

const float PlayerTest::NO_MONEY(0);
const float PlayerTest::MONEY_WON(10);
const float PlayerTest::INITIAL_AMOUNT_MONEY(5);
const float PlayerTest::TOO_MUCH_MONEY(10);
const float PlayerTest::BIG_BLIND(1);
const int PlayerTest::NUMBER_OF_RAISES(0);
const int PlayerTest::NUMBER_OF_PLAYERS(2);
const pokerGame::BettingRoundType PlayerTest::A_BETTING_ROUND_TYPE(pokerGame::PRE_FLOP);

TEST_F(PlayerTest, newPlayerIsNotPlaying) {
    pokerGame::Player newPlayer(0, INITIAL_AMOUNT_MONEY);
    bool playerIsPlaying = newPlayer.isPlaying();

    ASSERT_FALSE(playerIsPlaying);
}

TEST_F(PlayerTest, newPlayerHasInitialAmountOfMoney) {
    float initialMoney = aPlayer->getMoney();

    ASSERT_EQ(INITIAL_AMOUNT_MONEY, initialMoney);
}

TEST_F(PlayerTest, newPlayerHasNoMoneyInPot) {
    float initialPot = aPlayer->getPot();

    ASSERT_EQ(NO_MONEY, initialPot);
}

TEST_F(PlayerTest, playerIsPlayingAfterStarting) {
    aPlayer->startPlaying();

    bool playerIsPlaying = aPlayer->isPlaying();

    ASSERT_TRUE(playerIsPlaying);
}

TEST_F(PlayerTest, playerIsNotFoldedAfterSetupingANewTableTurn) {
    aPlayer->startPlaying();
    aPlayer->setupForNewRound();

    bool playerIsFolded = aPlayer->isFolded();

    ASSERT_FALSE(playerIsFolded);
}

TEST_F(PlayerTest, playerIsFoldedWhenFoldingAfterSetupingAnewTableTurn) {
    aPlayer->startPlaying();
    aPlayer->setupForNewRound();
    aPlayer->fold();

    bool playerIsFolded = aPlayer->isFolded();

    ASSERT_TRUE(playerIsFolded);
}

TEST_F(PlayerTest, playerPotIsClearedWhenSettingForNewTableTurn) {
    aPlayer->startPlaying();
    aPlayer->addToPot(INITIAL_AMOUNT_MONEY);
    aPlayer->setupForNewRound();

    float moneyInPot = aPlayer->getPot();

    ASSERT_EQ(PlayerTest::NO_MONEY, moneyInPot);
}

TEST_F(PlayerTest, playerHasMoreMoneyWhenWinningMoney) {
    aPlayer->winMoney(PlayerTest::MONEY_WON);

    float playersMoney = aPlayer->getMoney();

    ASSERT_EQ(PlayerTest::MONEY_WON + PlayerTest::INITIAL_AMOUNT_MONEY, playersMoney);
}

//TEST_F(PlayerTest, makingDecisionReturnsCallWhenPlayerCalls) {
//    pokerGame::Decision aDecision = {pokerGame::CALL, 0};
//    EXPECT_CALL(*aPlayerController, makeDecision(_, *sharedCards, 0, BIG_BLIND, bettingContext)).Times(1).WillOnce(Return(aDecision)); // TODO: _ should be player->hole

//    pokerGame::Decision returnedDecision = aPlayer->makeDecision(0, BIG_BLIND, *sharedCards, bettingContext);

//    ASSERT_EQ(aDecision.choice, returnedDecision.choice);
//    ASSERT_EQ(aDecision.bet, returnedDecision.bet);
//}

//TEST_F(PlayerTest, userIsAllInIfHeDoesNotHaveEnoughMoneyForHisDecision) {
//    pokerGame::Decision callDecision = {pokerGame::CALL, TOO_MUCH_MONEY};
//    EXPECT_CALL(*aPlayerController, makeDecision(_, *sharedCards, TOO_MUCH_MONEY, BIG_BLIND, _)).Times(1).WillOnce(Return(callDecision)); // TODO: _ should be player->hole

//    pokerGame::Decision returnedDecision = aPlayer->makeDecision(TOO_MUCH_MONEY, BIG_BLIND, *sharedCards, bettingContext);

//    ASSERT_TRUE(aPlayer->isAllIn());
//}

//TEST_F(PlayerTest, makingDecisionReturnsRaiseWhenPlayerRaisesAndHasEnoughMoney) {
//    aPlayer->setMoney(5);
//    pokerGame::Decision raiseDecision = {pokerGame::RAISE, 5};
//    EXPECT_CALL(*aPlayerController, makeDecision(_, *sharedCards, 0, BIG_BLIND, bettingContext)).Times(1).WillOnce(Return(raiseDecision)); // TODO: _ should be player->hole
//    pokerGame::Decision returnedDecision = aPlayer->makeDecision(0, BIG_BLIND, *sharedCards, bettingContext);

//    ASSERT_EQ(raiseDecision.choice, returnedDecision.choice);
//    ASSERT_EQ(raiseDecision.bet, returnedDecision.bet);
//}

//TEST_F(PlayerTest, playerFoldsWhenDecisionIsToFold) {
//    pokerGame::Decision foldDecision = {pokerGame::FOLD, 0};
//    EXPECT_CALL(*aPlayerController, makeDecision(_, *sharedCards, 0, BIG_BLIND, bettingContext)).Times(1).WillOnce(Return(foldDecision)); // TODO: _ should be player->hole

//    pokerGame::Decision returnedDecision = aPlayer->makeDecision(0, BIG_BLIND, *sharedCards, bettingContext);
//    bool playerFolded = aPlayer->isFolded();

//    ASSERT_EQ(foldDecision.choice, returnedDecision.choice);
//    ASSERT_EQ(foldDecision.bet, returnedDecision.bet);
//    ASSERT_TRUE(playerFolded);
//}
