#include "gtest/gtest.h"
#include <vector>
#include "pokerGame/GameRound.h"
#include "pokerGame/Card.h"
#include "PlayerMock.h"
#include "DeckMock.h"
#include "BettingRoundMock.h"
#include <string>

using ::testing::_;

using ::testing::Return;

namespace pokerGame {

class GameRoundTest : public ::testing::Test {
protected:
    pokerGame::GameRound* gameRound;
    pokerGame::GameContext* gameContext;

    test::PlayerMock* aPlayer;
    test::PlayerMock* anotherPlayer;
    test::DeckMock* deck;
    test::BettingRoundMock* bettingRound;
    pokerGame::Card* aCard;

    std::vector<pokerGame::Player*> players;

    static const int BIG_BLIND;
    static const int DEALER_INDEX;
    static const int BIG_BLIND_INDEX;
    static const int SMALL_BLIND_INDEX;
    static const int MONEY_WON;
    static const int A_BET;
    static std::string A_GAME_PHASE;
    static std::string PRE_FLOP_PHASE;
    static std::string FLOP_PHASE;
    static std::string TURN_PHASE;
    static std::string RIVER_PHASE;
    static std::string SHOWDOWN_PHASE;

    virtual void SetUp() {
        aCard = new pokerGame::Card(2, pokerGame::CLUB);
        aPlayer = new test::PlayerMock();
        anotherPlayer = new test::PlayerMock();
        deck = new test::DeckMock();
        bettingRound = new test::BettingRoundMock();
        gameContext = new pokerGame::GameContext(BIG_BLIND);
        gameContext->addPlayer(aPlayer);
        gameContext->addPlayer(anotherPlayer);
        gameContext->setBigBlindIndex(BIG_BLIND_INDEX);
        gameContext->setSmallBlindIndex(SMALL_BLIND_INDEX);
        gameContext->setDealerIndex(DEALER_INDEX);
        gameRound = new pokerGame::GameRound(deck, bettingRound);
        ON_CALL(*deck, draw()).WillByDefault(Return(*aCard));
    }
    virtual void TearDown() {
        delete aCard;
        delete deck;
        delete bettingRound;
        delete gameRound;
        delete gameContext;
    }

};

const int GameRoundTest::BIG_BLIND(2);
const int GameRoundTest::DEALER_INDEX(0);
const int GameRoundTest::BIG_BLIND_INDEX(1);
const int GameRoundTest::SMALL_BLIND_INDEX(0);
const int GameRoundTest::A_BET(2);
const int GameRoundTest::MONEY_WON(2);
std::string GameRoundTest::A_GAME_PHASE("PHASE");
std::string GameRoundTest::PRE_FLOP_PHASE("PreFlop");
std::string GameRoundTest::FLOP_PHASE("Flop");
std::string GameRoundTest::TURN_PHASE("Turn");
std::string GameRoundTest::RIVER_PHASE("River");
std::string GameRoundTest::SHOWDOWN_PHASE("Showdown");

TEST_F(GameRoundTest, bigAndSmallBlindPlayersAddTheirBlindsToTheirPotWhenBettingPot) {
    gameRound->initialize(gameContext);
    EXPECT_CALL(*aPlayer, addToPot(BIG_BLIND/2));
    EXPECT_CALL(*anotherPlayer, addToPot(BIG_BLIND));
    gameRound->betBlinds();
}

TEST_F(GameRoundTest, twoCardsAreAddedToEachPlayingPlayersHoleWhenDistributingHoles) {
    gameRound->initialize(gameContext);
    ON_CALL(*aPlayer, isPlaying()).WillByDefault(Return(true));
    ON_CALL(*anotherPlayer, isPlaying()).WillByDefault(Return(true));
    ON_CALL(*deck, draw()).WillByDefault(Return(*aCard));
    EXPECT_CALL(*aPlayer, addCardToHole(_)).Times(2);
    EXPECT_CALL(*anotherPlayer, addCardToHole(_)).Times(2);
    gameRound->distributeHoles();
}

TEST_F(GameRoundTest, holesAreNotDistributedToPlayersWhoAreNotPlaying) {
    gameRound->initialize(gameContext);
    ON_CALL(*anotherPlayer, isPlaying()).WillByDefault(Return(false));
    ON_CALL(*deck, draw()).WillByDefault(Return(*aCard));
    EXPECT_CALL(*aPlayer, addCardToHole(_)).Times(2);
    EXPECT_CALL(*anotherPlayer, addCardToHole(_)).Times(0);
    gameRound->distributeHoles();
}

TEST_F(GameRoundTest, everyPlayerSeePhaseNameWhenAnnouncingPhase) {
    gameRound->initialize(gameContext);
    EXPECT_CALL(*anotherPlayer, seeGamePhase(A_GAME_PHASE));
    EXPECT_CALL(*aPlayer, seeGamePhase(A_GAME_PHASE));
    gameRound->announcePhase(A_GAME_PHASE);
}


TEST_F(GameRoundTest, everyPlayerSeeWinnerWhenAnnouncingRoundWinner) {
    gameRound->initialize(gameContext);
    EXPECT_CALL(*anotherPlayer, seeRoundWinner(_, MONEY_WON)); //TODO: Find a way to mock calls with const ref parameters
    EXPECT_CALL(*aPlayer, seeRoundWinner(_, MONEY_WON)); // _ should be aPlayer
    gameRound->announceRoundWinner(aPlayer, MONEY_WON);
}

TEST_F(GameRoundTest, preFlopPhaseIsAnnouncedWhenItBegins) {
    gameRound->initialize(gameContext);
    EXPECT_CALL(*anotherPlayer, seeGamePhase(PRE_FLOP_PHASE));
    EXPECT_CALL(*aPlayer, seeGamePhase(PRE_FLOP_PHASE));
    gameRound->preFlop();
}

TEST_F(GameRoundTest, twoCardsAreDistributedInPreFlop) {
    gameRound->initialize(gameContext);
    ON_CALL(*aPlayer, isPlaying()).WillByDefault(Return(true));
    ON_CALL(*anotherPlayer, isPlaying()).WillByDefault(Return(true));
    EXPECT_CALL(*anotherPlayer, addCardToHole(_)).Times(2);
    EXPECT_CALL(*aPlayer, addCardToHole(_)).Times(2);
    gameRound->preFlop();
}

TEST_F(GameRoundTest, flopPhaseIsAnnouncedWhenItBegins) {
    gameRound->initialize(gameContext);
    EXPECT_CALL(*anotherPlayer, seeGamePhase(FLOP_PHASE));
    EXPECT_CALL(*aPlayer, seeGamePhase(FLOP_PHASE));
    gameRound->flop();
}

TEST_F(GameRoundTest, turnPhaseIsAnnouncedWhenItBegins) {
    gameRound->initialize(gameContext);
    EXPECT_CALL(*anotherPlayer, seeGamePhase(TURN_PHASE));
    EXPECT_CALL(*aPlayer, seeGamePhase(TURN_PHASE));
    gameRound->turn();
}

TEST_F(GameRoundTest, riverPhaseIsAnnouncedWhenItBegins) {
    gameRound->initialize(gameContext);
    EXPECT_CALL(*anotherPlayer, seeGamePhase(RIVER_PHASE));
    EXPECT_CALL(*aPlayer, seeGamePhase(RIVER_PHASE));
    gameRound->river();
}

TEST_F(GameRoundTest, showdownPhaseIsAnnouncedWhenItBegins) {
    gameRound->initialize(gameContext);
    EXPECT_CALL(*anotherPlayer, seeGamePhase(SHOWDOWN_PHASE));
    EXPECT_CALL(*aPlayer, seeGamePhase(SHOWDOWN_PHASE));
    gameRound->showdown();
}

TEST_F(GameRoundTest, theRoundWinnerWinsThePot) {
    gameRound->initialize(gameContext);
    EXPECT_CALL(*anotherPlayer, getPot()).Times(2).WillRepeatedly(Return(BIG_BLIND));
    EXPECT_CALL(*aPlayer, getPot()).Times(2).WillRepeatedly(Return(BIG_BLIND));
    EXPECT_CALL(*anotherPlayer, winMoney(2*BIG_BLIND));
    EXPECT_CALL(*anotherPlayer, hasBetterHand(_, _)).WillOnce(Return(true)); //TODO: find a way to replace _'s
    EXPECT_CALL(*aPlayer, hasBetterHand(_, _)).WillOnce(Return(false)); //TODO: find a way to replace _'s
    gameRound->showdown();
}

TEST_F(GameRoundTest, theRoundWinnerIsAnnouncedInShowndown) {
    gameRound->initialize(gameContext);
    EXPECT_CALL(*aPlayer, seeRoundWinner(_, 2* BIG_BLIND));
    EXPECT_CALL(*anotherPlayer, seeRoundWinner(_, 2* BIG_BLIND));
    EXPECT_CALL(*anotherPlayer, getPot()).Times(2).WillRepeatedly(Return(BIG_BLIND));
    EXPECT_CALL(*aPlayer, getPot()).Times(2).WillRepeatedly(Return(BIG_BLIND));
    EXPECT_CALL(*anotherPlayer, winMoney(2*BIG_BLIND));
    EXPECT_CALL(*anotherPlayer, hasBetterHand(_, _)).WillOnce(Return(true)); //TODO: find a way to replace _'s
    EXPECT_CALL(*aPlayer, hasBetterHand(_, _)).WillOnce(Return(false)); //TODO: find a way to replace _'s
    gameRound->showdown();
}

TEST_F(GameRoundTest, everyPlayersShowTheirCardsInShowdown) {
    gameRound->initialize(gameContext);
    EXPECT_CALL(*anotherPlayer, getPot()).Times(2).WillRepeatedly(Return(BIG_BLIND));
    EXPECT_CALL(*aPlayer, getPot()).Times(2).WillRepeatedly(Return(BIG_BLIND));
    EXPECT_CALL(*anotherPlayer, winMoney(2*BIG_BLIND));
    EXPECT_CALL(*anotherPlayer, hasBetterHand(_, _)).WillOnce(Return(true)); //TODO: find a way to replace _'s
    EXPECT_CALL(*aPlayer, hasBetterHand(_, _)).WillOnce(Return(false)); //TODO: find a way to replace _'s
    EXPECT_CALL(*anotherPlayer, showCards());
    EXPECT_CALL(*aPlayer, showCards());
    gameRound->showdown();
}

TEST_F(GameRoundTest, everyPlayersSeeTheirOponnentsCardsAndMoney) {
    gameRound->initialize(gameContext);
    EXPECT_CALL(*anotherPlayer, getPot()).Times(2).WillRepeatedly(Return(BIG_BLIND));
    EXPECT_CALL(*aPlayer, getPot()).Times(2).WillRepeatedly(Return(BIG_BLIND));
    EXPECT_CALL(*anotherPlayer, winMoney(2*BIG_BLIND));
    EXPECT_CALL(*anotherPlayer, hasBetterHand(_, _)).WillOnce(Return(true)); //TODO: find a way to replace _'s
    EXPECT_CALL(*aPlayer, hasBetterHand(_, _)).WillOnce(Return(false)); //TODO: find a way to replace _'s
    EXPECT_CALL(*anotherPlayer, seeOpponentMoney(_)).Times(2);
    EXPECT_CALL(*anotherPlayer, seeOpponentHole(_)).Times(2);
    EXPECT_CALL(*aPlayer, seeOpponentMoney(_)).Times(2);
    EXPECT_CALL(*aPlayer, seeOpponentHole(_)).Times(2);
    gameRound->showdown();
}

TEST_F(GameRoundTest, aBettingRoundStartsWhenExecutingNewBettingRound) {
    gameRound->initialize(gameContext);
    EXPECT_CALL(*bettingRound, start(gameContext, _)); //TODO: _ should be gameRound->sharedCards
    gameRound->executeNewBettingRound();
}

TEST_F(GameRoundTest, getNumberOfPlayingPlayersReturnsTheNumberOfPlayingPlayers) {
    gameRound->initialize(gameContext);
    EXPECT_CALL(*anotherPlayer, isPlaying()).WillOnce(Return(false));
    EXPECT_CALL(*aPlayer, isPlaying()).WillOnce(Return(true));

    int numberOfPlayingPlayers = gameRound->getNumberOfPlayingPlayers();

    ASSERT_EQ(1, numberOfPlayingPlayers);
}

TEST_F(GameRoundTest, deckIsShuffledWhenInitializingTheRound) {
    EXPECT_CALL(*deck, shuffle());
    gameRound->initialize(gameContext);
}

TEST_F(GameRoundTest, everyPlayersSetupForNewRoundWhenInitializingGameRound) {
    EXPECT_CALL(*anotherPlayer, setupForNewRound());
    EXPECT_CALL(*aPlayer, setupForNewRound());
    gameRound->initialize(gameContext);
}

}
