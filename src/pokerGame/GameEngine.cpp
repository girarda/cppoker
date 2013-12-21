#include "pokerGame/GameEngine.h"
#include <algorithm>
#include "boost/bind.hpp"
#include "boost/thread.hpp"

namespace pokerGame
{

GameEngine::GameEngine(GameContext* gameContext, GameRound* gameRoundToUse):
    context(gameContext),
    gameRound(gameRoundToUse),
    INITIAL_AMOUNT_OF_MONEY(10)
{
}

GameEngine::~GameEngine()
{
    for (std::vector<PokerPlayer*>::iterator it = context->players.begin(); it != context->players.end(); it++)
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
    for (PokerPlayer* p: context->players)
    {
        p->startPlaying();
    }
    while(getNumberOfPlayingPlayers() > 1)
    {
        playRound();
        if (numberOfRounds % 2 == 0)
            context->bigBlind *= 2;
    }
    announceWinner();
    endGame();
}

void GameEngine::endGame()
{
//    announcePhase("Game End");
    for (PokerPlayer* p: context->players)
    {
        p->stopPlaying();
    }
}

void GameEngine::playRound()
{
    chooseNextDealer();
    gameRound->playRound(context);
    numberOfRounds++;
}

void GameEngine::announceWinner()
{
    PokerPlayer* winner;
    for (PokerPlayer* p: context->players)
    {
        if (p->isPlaying())
        {
            winner = p;
            break;
        }
    }
    for (PokerPlayer* p: context->players)
    {
        p->seeWinner(*winner);
    }
}

void GameEngine::addPlayer(PokerPlayer* player)
{
    context->players.push_back(player);
}

void GameEngine::chooseNextDealer() // TODO: test this method
{
    context->dealerIndex++;
    context->dealerIndex %= context->players.size();

    context->bigBlindIndex = context->dealerIndex+1;
    context->bigBlindIndex %= context->players.size();

    context->smallBlindIndex = context->dealerIndex+2;
    context->smallBlindIndex %= context->players.size();
}

int GameEngine::getNumberOfPlayers() const
{
    return context->players.size();
}

int GameEngine::getNumberOfPlayingPlayers() const
{
    int count = 0;
    for (PokerPlayer* p: context->players)
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
    context->players.push_back(newPlayer);
    sendChatMessage("A new player joined!");
}

void GameEngine::leave(PlayerController* player) // TODO: test this method
{
    //players.erase(player);
}

void GameEngine::sendChatMessage(const std::string& msg) // TODO: test this method
{
    std::for_each(context->players.begin(), context->players.end(),
                  boost::bind(&PokerPlayer::deliver, _1, boost::ref(msg)));
}

}

