#include "gtest/gtest.h"
#include "pokerGame/GameEngine.h"
#include "PokerPlayermock.h"
#include "GameRoundMock.h"

using ::testing::Return;
using ::testing::_;

class GameEngineTest : public ::testing::Test
{
protected:
    pokerGame::GameEngine* game;
    pokerGame::GameContext* context;
    test::PlayerMock* aPlayer;
    test::PlayerMock* anotherPlayer;
    test::GameRoundMock* gameRound;

    static const int BIG_BLIND;
    static const int DEALER_INDEX;
    static const int BIG_BLIND_INDEX;
    static const int SMALL_BLIND_INDEX;

    virtual void SetUp()
    {
        aPlayer = new test::PlayerMock();
        anotherPlayer = new test::PlayerMock();
        gameRound = new test::GameRoundMock();
        context = new pokerGame::GameContext(BIG_BLIND);
        game = new pokerGame::GameEngine(context, gameRound);
    }
    virtual void TearDown()
    {
        delete game;
        delete gameRound;
        delete context;
    }

};

const int GameEngineTest::BIG_BLIND(2);
const int GameEngineTest::DEALER_INDEX(0);
const int GameEngineTest::BIG_BLIND_INDEX(1);
const int GameEngineTest::SMALL_BLIND_INDEX(0);

TEST_F(GameEngineTest, newGameHasNoPlayers)
{
    int nbOfPlayers = game->getNumberOfPlayers();

    ASSERT_EQ(0, nbOfPlayers);
}

TEST_F(GameEngineTest, addingAPlayerToTheGameIncreasesTheNuberOfPlayerInTheGame)
{
    game->addPlayer(aPlayer);

    int nbOfPlayers = game->getNumberOfPlayers();

    ASSERT_EQ(1, nbOfPlayers);
}

TEST_F(GameEngineTest, gameRoundPlaysRoundWhen)
{
    EXPECT_CALL(*gameRound, playRound(context));
    game->addPlayer(aPlayer);
    game->addPlayer(anotherPlayer);

    game->playRound();
}

TEST_F(GameEngineTest, startingANewGameMakesEveryPlayersStart)
{
    EXPECT_CALL(*anotherPlayer, lost()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*aPlayer, lost()).Times(1).WillRepeatedly(Return(true));
    EXPECT_CALL(*anotherPlayer, startPlaying()).Times(1);
    EXPECT_CALL(*aPlayer, startPlaying()).Times(1);
    game->addPlayer(aPlayer);
    game->addPlayer(anotherPlayer);

    game->start();
}

TEST_F(GameEngineTest, theWinnerIsAnnouncedAfterPlayingTheGame)
{
    EXPECT_CALL(*aPlayer, isPlaying()).WillOnce(Return(true)); //TODO: find a way to mock with const ref
    EXPECT_CALL(*aPlayer, seeWinner(_)); //TODO: find a way to mock with const ref
    game->addPlayer(aPlayer); // _ should be *player

    game->start();
}

TEST_F(GameEngineTest, ifThereAreMoreThanOnePlayerStillPlayingThenPlayARound)
{
    ON_CALL(*anotherPlayer, lost()).WillByDefault(Return(true));
    EXPECT_CALL(*anotherPlayer, lost()).Times(2).WillOnce(Return(false));
    EXPECT_CALL(*aPlayer, lost()).Times(2).WillRepeatedly(Return(false));
    EXPECT_CALL(*gameRound, playRound(context)).Times(1);
    game->addPlayer(aPlayer);
    game->addPlayer(anotherPlayer);

    game->start();
}

TEST_F(GameEngineTest, endingGameMakesEveryPlayersStopPlaying)
{
    EXPECT_CALL(*anotherPlayer, stopPlaying()).Times(1);
    EXPECT_CALL(*aPlayer, stopPlaying()).Times(1);
    game->addPlayer(aPlayer);
    game->addPlayer(anotherPlayer);

    game->endGame();
}
