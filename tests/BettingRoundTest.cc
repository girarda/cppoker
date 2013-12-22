#include "gtest/gtest.h"
#include <vector>
#include "pokerGame/BettingRound.h"
#include "PokerPlayermock.h"

using ::testing::_;

using ::testing::Return;

namespace pokerGame
{

class BettingRoundTest : public ::testing::Test
{
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

    virtual void SetUp()
    {
        aPlayer = new test::PlayerMock();
        anotherPlayer = new test::PlayerMock();
        gameContext = new pokerGame::GameContext(BIG_BLIND);
        gameContext->players.push_back(aPlayer);
        gameContext->players.push_back(anotherPlayer);
        gameContext->bigBlindIndex = BIG_BLIND_INDEX;
        gameContext->smallBlindIndex = SMALL_BLIND_INDEX;
        gameContext->dealerIndex = DEALER_INDEX;
        bettingRound = new pokerGame::BettingRound();


        ON_CALL(*aPlayer, isPlaying()).WillByDefault(Return(true));
        ON_CALL(*anotherPlayer, isPlaying()).WillByDefault(Return(true));
    }
    virtual void TearDown()
    {
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

TEST_F(BettingRoundTest, playersMakeDecisionIfTheyArePlaying)
{
    pokerGame::Decision aDecision = {pokerGame::FOLD, 0};
    ON_CALL(*anotherPlayer, makeDecision(A_BET, BIG_BLIND, sharedCards, NUMBER_OF_RAISES, gameContext->players.size())).WillByDefault(Return(aDecision));
    EXPECT_CALL(*anotherPlayer, makeDecision(A_BET, BIG_BLIND, sharedCards, NUMBER_OF_RAISES, gameContext->players.size()));
    EXPECT_CALL(*anotherPlayer, isPlaying());
    ON_CALL(*aPlayer, makeDecision(A_BET, BIG_BLIND, sharedCards, NUMBER_OF_RAISES, gameContext->players.size())).WillByDefault(Return(aDecision));
    EXPECT_CALL(*aPlayer, makeDecision(A_BET, BIG_BLIND, sharedCards, NUMBER_OF_RAISES, gameContext->players.size()));
    EXPECT_CALL(*aPlayer, isPlaying());
    bettingRound->start(gameContext, sharedCards);
}

TEST_F(BettingRoundTest, playersDoNotMakeDecisionsIfTheyAreNotPlaying)
{
    ON_CALL(*anotherPlayer, isPlaying()).WillByDefault(Return(false));
    EXPECT_CALL(*anotherPlayer, makeDecision(_, _, sharedCards, NUMBER_OF_RAISES, gameContext->players.size())).Times(0);
    EXPECT_CALL(*anotherPlayer, isPlaying());
    ON_CALL(*aPlayer, isPlaying()).WillByDefault(Return(false));
    EXPECT_CALL(*aPlayer, makeDecision(_, _, sharedCards, NUMBER_OF_RAISES, gameContext->players.size())).Times(0);
    EXPECT_CALL(*aPlayer, isPlaying());
    bettingRound->start(gameContext, sharedCards);
}

TEST_F(BettingRoundTest, whenAPlayerRaisesTheMinimumBetIsRaised)
{
    pokerGame::Decision aDecision = {pokerGame::CHECK, 0};
    pokerGame::Decision raiseDecision = {pokerGame::CALL, BIG_BLIND};
    ON_CALL(*anotherPlayer, makeDecision(_, BIG_BLIND, sharedCards, _, gameContext->players.size())).WillByDefault(Return(aDecision));
    EXPECT_CALL(*anotherPlayer, makeDecision(_, BIG_BLIND, sharedCards, _, gameContext->players.size())).Times(2);
    EXPECT_CALL(*anotherPlayer, isPlaying()).Times(2);
    ON_CALL(*aPlayer, makeDecision(_, BIG_BLIND, sharedCards, _, gameContext->players.size())).WillByDefault(Return(aDecision));
    EXPECT_CALL(*aPlayer, makeDecision(_, BIG_BLIND, sharedCards, _, gameContext->players.size())).Times(2).WillOnce(Return(raiseDecision)).WillOnce(Return(aDecision));
    EXPECT_CALL(*aPlayer, isPlaying()).Times(2);
    bettingRound->start(gameContext, sharedCards);

    float newMinBet = bettingRound->getMinBet();
    float expectedMinBet = A_BET + BIG_BLIND;
    ASSERT_EQ(expectedMinBet, newMinBet);
}

TEST_F(BettingRoundTest, everyPlayersSeePlayerTurnWhenAnnoucingPlayerTurn)
{
    ON_CALL(*anotherPlayer, isPlaying()).WillByDefault(Return(false));
    ON_CALL(*aPlayer, isPlaying()).WillByDefault(Return(false));
    EXPECT_CALL(*aPlayer, seePlayerTurn(_)).Times(2); //TODO: Find a way to mock calls with const ref parameters
    EXPECT_CALL(*anotherPlayer, seePlayerTurn(_)).Times(2);
    bettingRound->start(gameContext, sharedCards);
}

TEST_F(BettingRoundTest, thePlayersSeeWhoTheDealerIsWhenItIsTheirTurn)
{
    ON_CALL(*anotherPlayer, isPlaying()).WillByDefault(Return(false));
    ON_CALL(*aPlayer, isPlaying()).WillByDefault(Return(false));
    EXPECT_CALL(*aPlayer, seeDealer(_)); //TODO: Find a way to mock calls with const ref parameters
    EXPECT_CALL(*anotherPlayer, seeDealer(_)); //TODO: Find a way to mock calls with const ref parameters
    bettingRound->start(gameContext, sharedCards);
}

TEST_F(BettingRoundTest, announcementsShowsToThePlayerTheBigBlind)
{
    ON_CALL(*anotherPlayer, isPlaying()).WillByDefault(Return(false));
    ON_CALL(*aPlayer, isPlaying()).WillByDefault(Return(false));
    EXPECT_CALL(*aPlayer, seeBigBlind(_, BIG_BLIND)); //TODO: Find a way to mock calls with const ref parameters
    EXPECT_CALL(*anotherPlayer, seeBigBlind(_, BIG_BLIND)); //TODO: Find a way to mock calls with const ref parameters
    bettingRound->start(gameContext, sharedCards);
}

TEST_F(BettingRoundTest, ifEveryPlayerCheckThenEveryPlayerDecidesOnce)
{
    pokerGame::Decision aDecision = {pokerGame::CHECK, 0};
    ON_CALL(*aPlayer, makeDecision(A_BET, BIG_BLIND, sharedCards, NUMBER_OF_RAISES, gameContext->players.size())).WillByDefault(Return(aDecision));
    ON_CALL(*anotherPlayer, makeDecision(A_BET, BIG_BLIND, sharedCards, NUMBER_OF_RAISES, gameContext->players.size())).WillByDefault(Return(aDecision));

    EXPECT_CALL(*anotherPlayer, makeDecision(A_BET, BIG_BLIND, sharedCards, NUMBER_OF_RAISES, gameContext->players.size())).Times(1);
    EXPECT_CALL(*aPlayer, makeDecision(A_BET, BIG_BLIND, sharedCards, NUMBER_OF_RAISES, gameContext->players.size())).Times(1);

    bettingRound->start(gameContext, sharedCards);
}

TEST_F(BettingRoundTest, ifAPlayerRaisesThenThePlayingPlayersMustMakeAnotherDecision)
{
    pokerGame::Decision aDecision = {pokerGame::CHECK, 0};
    pokerGame::Decision raiseDecision = {pokerGame::CALL, 2};

    EXPECT_CALL(*anotherPlayer, makeDecision(A_BET+BIG_BLIND, BIG_BLIND, sharedCards, NUMBER_OF_RAISES+1, gameContext->players.size())).Times(1).WillOnce(Return(aDecision));
    EXPECT_CALL(*anotherPlayer, makeDecision(A_BET, BIG_BLIND, sharedCards, NUMBER_OF_RAISES, gameContext->players.size())).Times(1).WillOnce(Return(raiseDecision));
    EXPECT_CALL(*aPlayer, makeDecision(_, BIG_BLIND, sharedCards, _, gameContext->players.size())).Times(2).WillRepeatedly(Return(aDecision));

    bettingRound->start(gameContext, sharedCards);
}

}


