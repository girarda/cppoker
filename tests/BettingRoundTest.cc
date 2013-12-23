#include "gtest/gtest.h"
#include <vector>
#include "pokerGame/BettingRound.h"
#include "PlayerMock.h"

using ::testing::_;

using ::testing::Return;

namespace pokerGame {

class BettingRoundTest : public ::testing::Test {
protected:
    pokerGame::BettingRound* bettingRound;

    test::PlayerMock* aPlayer;
    test::PlayerMock* anotherPlayer;

    std::vector<pokerGame::Card> sharedCards;
    pokerGame::GameContext* gameContext;

    static const float BIG_BLIND;
    static const int DEALER_INDEX;
    static const int BIG_BLIND_INDEX;
    static const int SMALL_BLIND_INDEX;
    static const float A_BET;
    static const int NUMBER_OF_RAISES;

    virtual void SetUp() {
        aPlayer = new test::PlayerMock();
        anotherPlayer = new test::PlayerMock();
        gameContext = new pokerGame::GameContext(BIG_BLIND);
        gameContext->addPlayer(aPlayer);
        gameContext->addPlayer(anotherPlayer);
        gameContext->setBigBlindIndex(BIG_BLIND_INDEX);
        gameContext->setSmallBlindIndex(SMALL_BLIND_INDEX);
        gameContext->setDealerIndex(DEALER_INDEX);
        bettingRound = new pokerGame::BettingRound();

        ON_CALL(*aPlayer, isPlaying()).WillByDefault(Return(true));
        ON_CALL(*anotherPlayer, isPlaying()).WillByDefault(Return(true));
    }
    virtual void TearDown() {
        delete bettingRound;
        delete anotherPlayer;
        delete aPlayer;
    }

};

const float BettingRoundTest::BIG_BLIND(2);
const int BettingRoundTest::DEALER_INDEX(0);
const int BettingRoundTest::BIG_BLIND_INDEX(1);
const int BettingRoundTest::SMALL_BLIND_INDEX(0);
const float BettingRoundTest::A_BET(2);
const int BettingRoundTest::NUMBER_OF_RAISES(0);

TEST_F(BettingRoundTest, playersMakeDecisionIfTheyArePlaying) {
    pokerGame::Decision aDecision = {pokerGame::FOLD, 0};
    ON_CALL(*anotherPlayer, makeDecision(A_BET, BIG_BLIND, sharedCards, NUMBER_OF_RAISES, gameContext->getPlayers().size())).WillByDefault(Return(aDecision));
    EXPECT_CALL(*anotherPlayer, makeDecision(A_BET, BIG_BLIND, sharedCards, NUMBER_OF_RAISES, gameContext->getPlayers().size()));
    ON_CALL(*aPlayer, makeDecision(A_BET, BIG_BLIND, sharedCards, NUMBER_OF_RAISES, gameContext->getPlayers().size())).WillByDefault(Return(aDecision));
    EXPECT_CALL(*aPlayer, makeDecision(A_BET, BIG_BLIND, sharedCards, NUMBER_OF_RAISES, gameContext->getPlayers().size()));
    bettingRound->start(gameContext, sharedCards);
}

TEST_F(BettingRoundTest, playersDoNotMakeDecisionsIfTheyAreNotPlaying) {
    ON_CALL(*anotherPlayer, isPlaying()).WillByDefault(Return(false));
    EXPECT_CALL(*anotherPlayer, makeDecision(_, _, sharedCards, NUMBER_OF_RAISES, gameContext->getPlayers().size())).Times(0);
    ON_CALL(*aPlayer, isPlaying()).WillByDefault(Return(false));
    EXPECT_CALL(*aPlayer, makeDecision(_, _, sharedCards, NUMBER_OF_RAISES, gameContext->getPlayers().size())).Times(0);

    bettingRound->start(gameContext, sharedCards);
}

TEST_F(BettingRoundTest, whenAPlayerRaisesTheMinimumBetIsRaisedAndPlayingPlayersMustMakeAnotherDecision) {
    pokerGame::Decision aDecision = {pokerGame::CALL, 0};
    pokerGame::Decision raiseDecision = {pokerGame::RAISE, BIG_BLIND};
    ON_CALL(*anotherPlayer, isPlaying()).WillByDefault(Return(true));
    ON_CALL(*aPlayer, isPlaying()).WillByDefault(Return(true));
    ON_CALL(*anotherPlayer, makeDecision(_, BIG_BLIND, sharedCards, _, gameContext->getPlayers().size())).WillByDefault(Return(aDecision));

    ON_CALL(*aPlayer, makeDecision(_, BIG_BLIND, sharedCards, _, gameContext->getPlayers().size())).WillByDefault(Return(aDecision));
    EXPECT_CALL(*aPlayer, makeDecision(_, BIG_BLIND, sharedCards, _, gameContext->getPlayers().size())).Times(2).WillOnce(Return(raiseDecision));

    ON_CALL(*anotherPlayer, getPot()).WillByDefault(Return(2*BIG_BLIND));
    ON_CALL(*aPlayer, getPot()).WillByDefault(Return(2*BIG_BLIND));
    EXPECT_CALL(*anotherPlayer, getPot()).Times(8).WillOnce(Return(BIG_BLIND)).WillOnce(Return(BIG_BLIND)).WillOnce(Return(BIG_BLIND)).WillOnce(Return(BIG_BLIND)).WillOnce(Return(BIG_BLIND));

    bettingRound->start(gameContext, sharedCards);

    float newMinBet = bettingRound->getCurrentMinimumBid();
    float expectedMinBet = A_BET + BIG_BLIND;
    ASSERT_EQ(expectedMinBet, newMinBet);
}

TEST_F(BettingRoundTest, everyPlayersSeePlayerTurnWhenAnnoucingPlayerTurn) {
    ON_CALL(*aPlayer, isPlaying()).WillByDefault(Return(false));
    ON_CALL(*anotherPlayer, isPlaying()).WillByDefault(Return(false));
    EXPECT_CALL(*aPlayer, seePlayerTurn(_)).Times(1);
    EXPECT_CALL(*anotherPlayer, seePlayerTurn(_)).Times(1);
    bettingRound->start(gameContext, sharedCards);
}

TEST_F(BettingRoundTest, thePlayersSeeWhoTheDealerIsWhenItIsTheirTurn) {
    pokerGame::Decision aDecision = {pokerGame::CALL, 0};
    ON_CALL(*aPlayer, makeDecision(_, BIG_BLIND, sharedCards, _, gameContext->getPlayers().size())).WillByDefault(Return(aDecision));
    ON_CALL(*aPlayer, isPlaying()).WillByDefault(Return(false));
    EXPECT_CALL(*anotherPlayer, isPlaying()).Times(2).WillOnce(Return(false)).WillOnce(Return(false));
    EXPECT_CALL(*aPlayer, seeDealer(_));
    bettingRound->start(gameContext, sharedCards);
}

TEST_F(BettingRoundTest, announcementsShowsToThePlayerTheBigBlind) {
    pokerGame::Decision aDecision = {pokerGame::CALL, 0};
    ON_CALL(*aPlayer, makeDecision(_, BIG_BLIND, sharedCards, _, gameContext->getPlayers().size())).WillByDefault(Return(aDecision));
    ON_CALL(*aPlayer, isPlaying()).WillByDefault(Return(false));
    EXPECT_CALL(*anotherPlayer, isPlaying()).Times(2).WillOnce(Return(false)).WillOnce(Return(false));
    EXPECT_CALL(*aPlayer, seeBigBlind(_, BIG_BLIND));
    bettingRound->start(gameContext, sharedCards);
}

TEST_F(BettingRoundTest, ifEveryPlayerCallThenEveryPlayerDecidesOnce) {
    pokerGame::Decision aDecision = {pokerGame::CALL, 0};
    ON_CALL(*aPlayer, makeDecision(A_BET, BIG_BLIND, sharedCards, NUMBER_OF_RAISES, gameContext->getPlayers().size())).WillByDefault(Return(aDecision));
    ON_CALL(*anotherPlayer, makeDecision(A_BET, BIG_BLIND, sharedCards, NUMBER_OF_RAISES, gameContext->getPlayers().size())).WillByDefault(Return(aDecision));

    EXPECT_CALL(*anotherPlayer, makeDecision(A_BET, BIG_BLIND, sharedCards, NUMBER_OF_RAISES, gameContext->getPlayers().size())).Times(1);
    EXPECT_CALL(*aPlayer, makeDecision(A_BET, BIG_BLIND, sharedCards, NUMBER_OF_RAISES, gameContext->getPlayers().size())).Times(1);

    bettingRound->start(gameContext, sharedCards);
}

}
