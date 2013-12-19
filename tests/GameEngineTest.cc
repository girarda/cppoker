#include "gtest/gtest.h"
#include "pokerGame/GameEngine.h"
#include "PokerPlayermock.h"

using ::testing::Return;

class BettingRoundTest : public ::testing::Test
{
protected:
    pokerGame::GameEngine game;

    test::PlayerMock* aPlayer;
    test::PlayerMock* anotherPlayer;

    virtual void SetUp()
    {
        aPlayer = new test::PlayerMock();
        anotherPlayer = new test::PlayerMock();
    }
    virtual void TearDown()
    {
    }

};

//TEST_F(BettingRoundTest, newGameHasNoPlayers)
//{
//    int nbOfPlayers = game.getNumberOfPlayers();

//    ASSERT_EQ(0, nbOfPlayers);
//}

//TEST_F(BettingRoundTest, addingAPlayerToTheGameIncreasesTheNuberOfPlayerInTheGame)
//{
//    game.addPlayer(aPlayer);

//    int nbOfPlayers = game.getNumberOfPlayers();

//    ASSERT_EQ(1, nbOfPlayers);
//}

//TEST_F(BettingRoundTest, initatingATableTurnSetsThePlayerForATableTurn)
//{
//    EXPECT_CALL(*anotherPlayer, setupForNewTableTurn()).Times(1);
//    EXPECT_CALL(*aPlayer, setupForNewTableTurn()).Times(1);
//    game.addPlayer(aPlayer);
//    game.addPlayer(anotherPlayer);

//    game.initRound();
//}

//TEST_F(BettingRoundTest, startingANewGameMakesEveryPlayersStart)
//{
//    ON_CALL(*aPlayer, isPlaying()).WillByDefault(Return(true));
//    EXPECT_CALL(*aPlayer, startPlaying()).Times(1);
//    game.addPlayer(aPlayer);

//    game.start();
//}
