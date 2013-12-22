#include "pokerGame/GameEngine.h"
#include <algorithm>
#include "boost/bind.hpp"
#include "boost/thread.hpp"
#include <iostream>

namespace pokerGame {

GameEngine::GameEngine(GameContext* gameContext, GameRound* gameRoundToUse):
    context(gameContext),
    gameRound(gameRoundToUse),
    INITIAL_AMOUNT_OF_MONEY(10) {
}

GameEngine::~GameEngine() {
}

void GameEngine::start() {
    std::cout << "Game start" << std::endl;
    //    announcePhase("Game Start");
    for (Player* p: context->getPlayers()) {
        p->startPlaying();
    }
    while(context->getNumberOfPlayingPlayers() > 1) {
        playRound();
        if (numberOfRounds % 2 == 0) {
            context->doubleBigBlind();
        }
    }
    announceWinner();
    endGame();
}

void GameEngine::endGame() {
    std::cout << "Game end" << std::endl;
    //    announcePhase("Game End");
    for (Player* p: context->getPlayers()) {
        p->stopPlaying();
    }
}

void GameEngine::playRound() {
    std::cout << "Round " << numberOfRounds << std::endl;
    context->chooseNextDealer();
    gameRound->playRound(context);
    numberOfRounds++;
}

void GameEngine::announceWinner() {
    Player* winner;
    for (Player* p: context->getPlayers()) {
        if (p->isPlaying()) {
            winner = p;
            break;
        }
    }
    for (Player* p: context->getPlayers()) {
        p->seeWinner(*winner);
    }
    //std::cout << "The winner is " << winner->getName() << std::endl;
}

void GameEngine::addPlayer(Player* player) {
    context->addPlayer(player);
}

int GameEngine::getNumberOfPlayers() const {
    return context->getNumberOfPlayers();
}

void GameEngine::join(PlayerController* player) {// TODO: test this method
    Player* newPlayer = new Player(player, INITIAL_AMOUNT_OF_MONEY);
    context->addPlayer(newPlayer);
    sendChatMessage("A new player joined!");
}

void GameEngine::leave(PlayerController* player) {// TODO: test this method
    //players.erase(player);
}

void GameEngine::sendChatMessage(const std::string& msg) {// TODO: test this method
    std::for_each(context->getPlayers().begin(), context->getPlayers().end(),
                  boost::bind(&Player::deliver, _1, boost::ref(msg)));
}

}
