#include "gtest/gtest.h"
#include "pokerGame/Player.h"
#include "PlayerControllerMock.h"
#include "pokerGame/OpponentModel.h"
#include "pokerGame/PlayerController.h"
#include "pokerGame/context/BettingContext.h"

using ::testing::Return;
using ::testing::_;

class PlayerTest : public ::testing::Test {
protected:
    test::PlayerControllerMock* aPlayerController;
    pokerGame::Player* aPlayer;
    pokerGame::context::BettingContext* bettingContext;
    std::vector<pokerGame::card::Card>* sharedCards;
    std::vector<pokerGame::OpponentModel> opponentModels;

    static const float NO_MONEY;
    static const float MONEY_WON;
    static const float INITIAL_AMOUNT_MONEY;
    static const float TOO_MUCH_MONEY;
    static const float BIG_BLIND;
    static const int NUMBER_OF_RAISES;
    static const int NUMBER_OF_PLAYERS;
    static const pokerGame::BettingRoundType A_BETTING_ROUND_TYPE;
    static const pokerGame::card::Card A_CARD;
    static const pokerGame::card::Card ANOTHER_CARD;
    static const std::string GAME_PHASE;
    static const std::string PLAYER_NAME;
    static const std::string A_MESSAGE;

    virtual void SetUp() {
        aPlayerController = new test::PlayerControllerMock();
        sharedCards = new std::vector<pokerGame::card::Card>();
        aPlayer = new pokerGame::Player(aPlayerController, INITIAL_AMOUNT_MONEY);
        aPlayer->startPlaying();
        bettingContext = new pokerGame::context::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS);
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
const pokerGame::card::Card PlayerTest::A_CARD(2, pokerGame::card::CLUB);
const pokerGame::card::Card PlayerTest::ANOTHER_CARD(5, pokerGame::card::DIAMOND);
const std::string PlayerTest::GAME_PHASE("GAME_PHASE");
const std::string PlayerTest::PLAYER_NAME("PLAYER_NAME");
const std::string PlayerTest::A_MESSAGE("A_MESSAGE");

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

TEST_F(PlayerTest, playerPotIsClearedWhenSettingForNewGameRound) {
    aPlayer->startPlaying();
    aPlayer->addToPot(INITIAL_AMOUNT_MONEY);
    aPlayer->setupForNewRound();

    float moneyInPot = aPlayer->getPot();

    ASSERT_EQ(PlayerTest::NO_MONEY, moneyInPot);
}

TEST_F(PlayerTest, playerHasNoHoleCardsAfterSettingUpForNewGameRound) {
    aPlayer->startPlaying();
    aPlayer->addCardToHole(A_CARD);
    aPlayer->addCardToHole(ANOTHER_CARD);

    aPlayer->setupForNewRound();

    std::vector<pokerGame::card::Card> holeCards = aPlayer->getVisibleHoleCards();
    ASSERT_TRUE(holeCards.empty());
}


TEST_F(PlayerTest, playerHasMoreMoneyWhenWinningMoney) {
    aPlayer->winMoney(PlayerTest::MONEY_WON);
    float playersMoney = aPlayer->getMoney();
    ASSERT_EQ(PlayerTest::MONEY_WON + PlayerTest::INITIAL_AMOUNT_MONEY, playersMoney);
}

TEST_F(PlayerTest, canSetPlayerMoney) {
    aPlayer->setMoney(NO_MONEY);
    float playersMoney = aPlayer->getMoney();
    ASSERT_EQ(NO_MONEY, playersMoney);
}

TEST_F(PlayerTest, playerIsAllInIfHeIsPlayingAndHasNoMoreMoney) {
    aPlayer->startPlaying();
    aPlayer->setMoney(NO_MONEY);

    bool isAllIn = aPlayer->isAllIn();

    ASSERT_TRUE(isAllIn);
}

TEST_F(PlayerTest, playerControllerSeesGamePhaseWhenSeeGamePhaseIsCalled) {
    EXPECT_CALL(*aPlayerController, seeGamePhase(GAME_PHASE));
    aPlayer->seeGamePhase(GAME_PHASE);
}

TEST_F(PlayerTest, playerControllerSeesPlayerTurnWhenSeePlayerTurnIsCalled) {
    EXPECT_CALL(*aPlayerController, getName()).WillRepeatedly(Return(PLAYER_NAME));
    EXPECT_CALL(*aPlayerController, seePlayerTurn(aPlayer->getName()));
    aPlayer->seePlayerTurn(*aPlayer);
}

TEST_F(PlayerTest, playerControllerSeesDealerWhenSeeDealerIsCalled) {
    EXPECT_CALL(*aPlayerController, getName()).WillRepeatedly(Return(PLAYER_NAME));
    EXPECT_CALL(*aPlayerController, seeDealer(aPlayer->getName()));
    aPlayer->seeDealer(*aPlayer);
}

TEST_F(PlayerTest, playerControllerSeesBigBlindWhenSeeBigBlindIsCalled) {
    EXPECT_CALL(*aPlayerController, getName()).WillRepeatedly(Return(PLAYER_NAME));
    EXPECT_CALL(*aPlayerController, seeBigBlind(aPlayer->getName(), BIG_BLIND));
    aPlayer->seeBigBlind(*aPlayer, BIG_BLIND);
}

TEST_F(PlayerTest, playerControllerSeesSmallBlindWhenSeeSmallBlindIsCalled) {
    EXPECT_CALL(*aPlayerController, getName()).WillRepeatedly(Return(PLAYER_NAME));
    EXPECT_CALL(*aPlayerController, seeSmallBlind(aPlayer->getName(), BIG_BLIND/2));
    aPlayer->seeSmallBlind(*aPlayer, BIG_BLIND/2);
}

TEST_F(PlayerTest, playerControllerSeesRoundWinnerWhenSeeRoundWinnerIsCalled) {
    EXPECT_CALL(*aPlayerController, getName()).WillRepeatedly(Return(PLAYER_NAME));
    EXPECT_CALL(*aPlayerController, seeRoundWinner(aPlayer->getName(), MONEY_WON));
    aPlayer->seeRoundWinner(*aPlayer, MONEY_WON);
}

TEST_F(PlayerTest, playerControllerSeesWinnerWhenSeeWinnerIsCalled) {
    EXPECT_CALL(*aPlayerController, getName()).WillRepeatedly(Return(PLAYER_NAME));
    EXPECT_CALL(*aPlayerController, seeWinner(aPlayer->getName()));
    aPlayer->seeWinner(*aPlayer);
}

TEST_F(PlayerTest, playerControllerSeesOpponentHoleCardsWhenSeeOpponentHoleCardsIsCalled) {
    EXPECT_CALL(*aPlayerController, getName()).WillRepeatedly(Return(PLAYER_NAME));
    EXPECT_CALL(*aPlayerController, seeOpponentHole(aPlayer->getName(), _));

    aPlayer->addCardToHole(A_CARD);
    aPlayer->addCardToHole(ANOTHER_CARD);
    aPlayer->seeOpponentHoleCards(*aPlayer);
}

TEST_F(PlayerTest, playerControllerSeesOpponentMoneyWhenSeeOpponentMoneyIsCalled) {
    EXPECT_CALL(*aPlayerController, getName()).WillRepeatedly(Return(PLAYER_NAME));
    EXPECT_CALL(*aPlayerController, seeOpponentMoney(aPlayer->getName(), INITIAL_AMOUNT_MONEY));

    aPlayer->seeOpponentMoney(*aPlayer);
}

TEST_F(PlayerTest, playerControllerSeesHoleCardsWhenSeeHoleCardsIsCalled) {
    EXPECT_CALL(*aPlayerController, seeHole(_));

    aPlayer->addCardToHole(A_CARD);
    aPlayer->addCardToHole(ANOTHER_CARD);
    aPlayer->seeHoleCards();
}

TEST_F(PlayerTest, playerControllerSeesMoneyWhenSeeMoneyIsCalled) {
    EXPECT_CALL(*aPlayerController, seeMoney(INITIAL_AMOUNT_MONEY));
    aPlayer->seeMoney();
}

TEST_F(PlayerTest, getVisibleHoleReturnsOnlyVisibleCards) {
    aPlayer->addCardToHole(A_CARD);
    aPlayer->addCardToHole(ANOTHER_CARD);

    std::vector<pokerGame::card::Card> visibleHoleCards = aPlayer->getVisibleHoleCards();
    ASSERT_EQ(1, visibleHoleCards.size());
    ASSERT_EQ(ANOTHER_CARD, visibleHoleCards[0]);
}

TEST_F(PlayerTest, allCardsAreVisibleAfterShowingCards) {
    aPlayer->addCardToHole(A_CARD);
    aPlayer->addCardToHole(ANOTHER_CARD);

    aPlayer->showCards();

    std::vector<pokerGame::card::Card> visibleHoleCards = aPlayer->getVisibleHoleCards();
    ASSERT_EQ(2, visibleHoleCards.size());
}

TEST_F(PlayerTest, playerControllerDeliversWhenDeliverIsCalled) {
    EXPECT_CALL(*aPlayerController, deliver(A_MESSAGE));
    aPlayer->deliver(A_MESSAGE);
}

TEST_F(PlayerTest, canGetPlayerMoney) {
    float money = aPlayer->getMoney();
    ASSERT_EQ(INITIAL_AMOUNT_MONEY, money);
}

TEST_F(PlayerTest, makingDecisionReturnsCallWhenPlayerCalls) {
    pokerGame::Decision aDecision = {pokerGame::CALL, 0};
    EXPECT_CALL(*aPlayerController, makeDecision(_, *sharedCards, 0, BIG_BLIND, bettingContext, opponentModels)).Times(1).WillOnce(Return(aDecision));

    pokerGame::Decision returnedDecision = aPlayer->makeDecision(0, BIG_BLIND, *sharedCards, bettingContext, opponentModels);

    ASSERT_EQ(aDecision.choice, returnedDecision.choice);
    ASSERT_EQ(aDecision.bet, returnedDecision.bet);
}

TEST_F(PlayerTest, userIsAllInIfHeDoesNotHaveEnoughMoneyForHisDecision) {
    pokerGame::Decision callDecision = {pokerGame::CALL, TOO_MUCH_MONEY};
    EXPECT_CALL(*aPlayerController, makeDecision(_, *sharedCards, TOO_MUCH_MONEY, BIG_BLIND, bettingContext, opponentModels)).Times(1).WillOnce(Return(callDecision));

    pokerGame::Decision returnedDecision = aPlayer->makeDecision(TOO_MUCH_MONEY, BIG_BLIND, *sharedCards, bettingContext, opponentModels);

    ASSERT_TRUE(aPlayer->isAllIn());
}

TEST_F(PlayerTest, makingDecisionReturnsRaiseWhenPlayerRaisesAndHasEnoughMoney) {
    aPlayer->setMoney(5);
    pokerGame::Decision raiseDecision = {pokerGame::RAISE, 5};
    EXPECT_CALL(*aPlayerController, makeDecision(_, *sharedCards, 0, BIG_BLIND, bettingContext, opponentModels)).Times(1).WillOnce(Return(raiseDecision));
    pokerGame::Decision returnedDecision = aPlayer->makeDecision(0, BIG_BLIND, *sharedCards, bettingContext, opponentModels);

    ASSERT_EQ(raiseDecision.choice, returnedDecision.choice);
    ASSERT_EQ(raiseDecision.bet, returnedDecision.bet);
}

TEST_F(PlayerTest, playerFoldsWhenDecisionIsToFold) {
    pokerGame::Decision foldDecision = {pokerGame::FOLD, 0};
    EXPECT_CALL(*aPlayerController, makeDecision(_, *sharedCards, 0, BIG_BLIND, bettingContext, opponentModels)).Times(1).WillOnce(Return(foldDecision));

    pokerGame::Decision returnedDecision = aPlayer->makeDecision(0, BIG_BLIND, *sharedCards, bettingContext, opponentModels);
    bool playerFolded = aPlayer->isFolded();

    ASSERT_EQ(foldDecision.choice, returnedDecision.choice);
    ASSERT_EQ(foldDecision.bet, returnedDecision.bet);
    ASSERT_TRUE(playerFolded);
}
