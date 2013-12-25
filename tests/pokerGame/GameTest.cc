#include "gtest/gtest.h"
#include "pokerGame/Game.h"
#include "tests/mocks/pokerGame/PlayerMock.h"
#include "tests/mocks/pokerGame/GameRoundMock.h"

using ::testing::Return;
using ::testing::_;

class GameTest : public ::testing::Test {
protected:
    pokerGame::Game* game;
    pokerGame::GameContext* context;
    test::PlayerMock* aPlayer;
    test::PlayerMock* anotherPlayer;
    test::GameRoundMock* gameRound;

    static const int BIG_BLIND;
    static const int DEALER_INDEX;
    static const int BIG_BLIND_INDEX;
    static const int SMALL_BLIND_INDEX;

    virtual void SetUp() {
        aPlayer = new test::PlayerMock();
        anotherPlayer = new test::PlayerMock();
        gameRound = new test::GameRoundMock();
        context = new pokerGame::GameContext(BIG_BLIND);
        game = new pokerGame::Game(context, gameRound);
    }

    virtual void TearDown() {
        delete game;
        delete gameRound;
        delete context;
    }

};

const int GameTest::BIG_BLIND(2);
const int GameTest::DEALER_INDEX(0);
const int GameTest::BIG_BLIND_INDEX(1);
const int GameTest::SMALL_BLIND_INDEX(0);

TEST_F(GameTest, newGameHasNoPlayers) {
    int nbOfPlayers = game->getNumberOfPlayers();

    ASSERT_EQ(0, nbOfPlayers);
    delete aPlayer;
    delete anotherPlayer;
}

TEST_F(GameTest, addingAPlayerToTheGameIncreasesTheNuberOfPlayerInTheGame) {
    game->addPlayer(aPlayer);

    int nbOfPlayers = game->getNumberOfPlayers();

    ASSERT_EQ(1, nbOfPlayers);
    delete anotherPlayer;
}

TEST_F(GameTest, gameRoundPlaysRoundWhen) {
    EXPECT_CALL(*gameRound, playRound(context));
    game->addPlayer(aPlayer);
    game->addPlayer(anotherPlayer);

    game->playRound();
}

TEST_F(GameTest, startingANewGameMakesEveryPlayersStart) {
    EXPECT_CALL(*anotherPlayer, getMoney()).Times(1).WillOnce(Return(0));
    EXPECT_CALL(*aPlayer, getMoney()).Times(1).WillRepeatedly(Return(0));
    EXPECT_CALL(*anotherPlayer, startPlaying()).Times(1);
    EXPECT_CALL(*aPlayer, startPlaying()).Times(1);
    game->addPlayer(aPlayer);
    game->addPlayer(anotherPlayer);

    game->start();
}

TEST_F(GameTest, theWinnerIsAnnouncedAfterPlayingTheGame) {
    EXPECT_CALL(*aPlayer, isPlaying()).WillOnce(Return(true));
    EXPECT_CALL(*aPlayer, seeWinner(_));
    game->addPlayer(aPlayer);

    game->start();
    delete anotherPlayer;
}

TEST_F(GameTest, ifThereAreMoreThanOnePlayerStillPlayingThenPlayARound) {
    ON_CALL(*anotherPlayer, getMoney()).WillByDefault(Return(0));
    EXPECT_CALL(*anotherPlayer, getMoney()).Times(2).WillOnce(Return(2));
    EXPECT_CALL(*aPlayer, getMoney()).Times(2).WillRepeatedly(Return(2));
    EXPECT_CALL(*gameRound, playRound(context)).Times(1);
    game->addPlayer(aPlayer);
    game->addPlayer(anotherPlayer);

    game->start();
}

TEST_F(GameTest, endingGameMakesEveryPlayersStopPlaying) {
    EXPECT_CALL(*anotherPlayer, stopPlaying()).Times(1);
    EXPECT_CALL(*aPlayer, stopPlaying()).Times(1);
    game->addPlayer(aPlayer);
    game->addPlayer(anotherPlayer);

    game->endGame();
}
