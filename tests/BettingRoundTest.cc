#include "gtest/gtest.h"
#include <vector>
#include "pokerGame/BettingRound.h"
#include "PokerPlayermock.h"

using ::testing::_;

using ::testing::Return;

class BettingRoundTest : public ::testing::Test
{
protected:
    pokerGame::BettingRound* bettingRound;

    test::PlayerMock* aPlayer;
    test::PlayerMock* anotherPlayer;

    std::vector<pokerGame::PokerPlayer*> players;

    static const int BIG_BLIND;
    static const int DEALER_INDEX;
    static const int BIG_BLIND_INDEX;
    static const int SMALL_BLIND_INDEX;
    static const int A_BET;

    virtual void SetUp()
    {
        aPlayer = new test::PlayerMock();
        anotherPlayer = new test::PlayerMock();
        players.push_back(aPlayer);
        players.push_back(anotherPlayer);
        bettingRound = new pokerGame::BettingRound(players, BIG_BLIND, DEALER_INDEX, BIG_BLIND_INDEX, SMALL_BLIND_INDEX);

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

const int BettingRoundTest::BIG_BLIND(2);
const int BettingRoundTest::DEALER_INDEX(0);
const int BettingRoundTest::BIG_BLIND_INDEX(1);
const int BettingRoundTest::SMALL_BLIND_INDEX(0);
const int BettingRoundTest::A_BET(2);

TEST_F(BettingRoundTest, playerTurnCallPlayerMakeDecisionIfPlayerIsPlaying)
{
    pokerGame::Decision aDecision = {pokerGame::FOLD, 0};
    ON_CALL(*aPlayer, makeDecision(A_BET, BIG_BLIND)).WillByDefault(Return(aDecision));
    EXPECT_CALL(*aPlayer, makeDecision(A_BET, BIG_BLIND));
    EXPECT_CALL(*aPlayer, isPlaying());
    bettingRound->playerTurn(aPlayer);
}

TEST_F(BettingRoundTest, playerDoesNotMakeDecisionsIfHeIsNotPlaying)
{
    ON_CALL(*aPlayer, isPlaying()).WillByDefault(Return(false));
    EXPECT_CALL(*aPlayer, makeDecision(_, _)).Times(0);
    EXPECT_CALL(*aPlayer, isPlaying());
    bettingRound->playerTurn(aPlayer);
}

TEST_F(BettingRoundTest, whenPlayersTurnIfPlayerRaisesThenBetIsRaised)
{
    pokerGame::Decision aDecision = {pokerGame::CALL, BIG_BLIND};
    ON_CALL(*aPlayer, makeDecision(A_BET, BIG_BLIND)).WillByDefault(Return(aDecision));
    EXPECT_CALL(*aPlayer, makeDecision(A_BET, BIG_BLIND));
    EXPECT_CALL(*aPlayer, isPlaying());
    bettingRound->playerTurn(aPlayer);

    float newMinBet = bettingRound->getMinBet();
    float expectedMinBet = A_BET + BIG_BLIND;
    ASSERT_EQ(expectedMinBet, newMinBet);
}

TEST_F(BettingRoundTest, everyPlayersSeePlayerTurnWhenAnnoucingPlayerTurn)
{
    EXPECT_CALL(*aPlayer, seePlayerTurn(_)); //TODO: Find a way to mock calls with const ref parameters
    EXPECT_CALL(*anotherPlayer, seePlayerTurn(_)); // _ should be aPlayer
    bettingRound->announcePlayerTurn(aPlayer);
}

TEST_F(BettingRoundTest, announcementsShowsToThePlayerTheDealer)
{
    EXPECT_CALL(*aPlayer, seeDealer(_)); //TODO: Find a way to mock calls with const ref parameters
    bettingRound->announcements(aPlayer); // _ should be aPlayer
}

TEST_F(BettingRoundTest, announcementsShowsToThePlayerTheBigBlind)
{
    EXPECT_CALL(*aPlayer, seeBigBlind(_, BIG_BLIND)); //TODO: Find a way to mock calls with const ref parameters
    bettingRound->announcements(aPlayer); // _ should be anotherPlayer
}

TEST_F(BettingRoundTest, ifEveryPlayerCheckThenEveryPlayerDecidesOnce)
{
    pokerGame::Decision aDecision = {pokerGame::CHECK, 0};
    ON_CALL(*aPlayer, makeDecision(A_BET, BIG_BLIND)).WillByDefault(Return(aDecision));
    ON_CALL(*anotherPlayer, makeDecision(A_BET, BIG_BLIND)).WillByDefault(Return(aDecision));

    EXPECT_CALL(*anotherPlayer, makeDecision(A_BET, BIG_BLIND)).Times(1);
    EXPECT_CALL(*aPlayer, makeDecision(A_BET, BIG_BLIND)).Times(1);

    bettingRound->start();
}

TEST_F(BettingRoundTest, test)
{
    pokerGame::Decision aDecision = {pokerGame::CHECK, 0};
    pokerGame::Decision raiseDecision = {pokerGame::CALL, 2};

    EXPECT_CALL(*anotherPlayer, makeDecision(A_BET+BIG_BLIND, BIG_BLIND)).Times(1).WillOnce(Return(aDecision));
    EXPECT_CALL(*anotherPlayer, makeDecision(A_BET, BIG_BLIND)).Times(1).WillOnce(Return(raiseDecision));
    EXPECT_CALL(*aPlayer, makeDecision(_, BIG_BLIND)).Times(2).WillRepeatedly(Return(aDecision));

    bettingRound->start();
}


