#include "pokerGame/GameEngine.h"
#include <algorithm>
#include "boost/bind.hpp"
#include "boost/thread.hpp"

namespace pokerGame
{

GameEngine::GameEngine(GameRound* gameRoundToUse):
    players(),
    bigBlind(2),
    bigBlindPlayerIndex(-1),
    smallBlindPlayerIndex(-1),
    dealerIndex(-1),
    bet(0),
    gameRound(gameRoundToUse),
    INITIAL_AMOUNT_OF_MONEY(10)
{
}

GameEngine::~GameEngine()
{
    for (std::vector<PokerPlayer*>::iterator it = players.begin(); it != players.end(); it++)
    {
        if (*it)
        {
            delete *it;
        }
    }
}

void GameEngine::start()
{

//    announcePhase("Game Start");
    for (PokerPlayer* p: players)
    {
        p->startPlaying();
    }
    while(getNumberOfPlayingPlayers() > 1)
    {
        playRound();
        if (numberOfRounds % 2 == 0)
            bigBlind *= 2;
    }
    announceWinner();
    endGame();
}

void GameEngine::endGame()
{
//    announcePhase("Game End");
    for (PokerPlayer* p: players)
    {
        p->stopPlaying();
    }
}

void GameEngine::playRound()
{
    chooseNextDealer();
    gameRound->playRound(players, bigBlind, dealerIndex, bigBlindPlayerIndex, smallBlindPlayerIndex);
    numberOfRounds++;
}

void GameEngine::announceWinner()
{
    PokerPlayer* winner;
    for (PokerPlayer* p: players)
    {
        if (p->isPlaying())
        {
            winner = p;
            break;
        }
    }
    for (PokerPlayer* p: players)
    {
        p->seeWinner(*winner);
    }
}

void GameEngine::addPlayer(PokerPlayer* player)
{
    players.push_back(player);
}

void GameEngine::chooseNextDealer() // TODO: test this method
{
    dealerIndex++;
    dealerIndex %= players.size();

    bigBlindPlayerIndex = dealerIndex+1;
    bigBlindPlayerIndex %= players.size();

    smallBlindPlayerIndex = dealerIndex+2;
    smallBlindPlayerIndex %= players.size();
}

int GameEngine::getNumberOfPlayers() const
{
    return players.size();
}

int GameEngine::getNumberOfPlayingPlayers() const
{
    int count = 0;
    for (PokerPlayer* p: players)
    {
        if(!p->lost()) {
            count++;
        }
    }
    return count;
}

void GameEngine::join(PlayerController* player) // TODO: test this method
{
    PokerPlayer* newPlayer = new PokerPlayer(player, INITIAL_AMOUNT_OF_MONEY);
    players.push_back(newPlayer);
    sendChatMessage("A new player joined!");
}

void GameEngine::leave(PlayerController* player) // TODO: test this method
{
    //players.erase(player);
}

void GameEngine::sendChatMessage(const std::string& msg) // TODO: test this method
{
    std::for_each(players.begin(), players.end(),
                  boost::bind(&PokerPlayer::deliver, _1, boost::ref(msg)));
}

}

