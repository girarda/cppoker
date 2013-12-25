#include "pokerGame/Game.h"
#include <algorithm>
#include "boost/bind.hpp"
#include "boost/thread.hpp"
#include <iostream>

namespace pokerGame {

Game::Game(GameContext* gameContext, GameRound* gameRoundToUse):
    context(gameContext),
    gameRound(gameRoundToUse),
    INITIAL_AMOUNT_OF_MONEY(10) {
}

Game::~Game() {
}

void Game::start() {
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

void Game::endGame() {
    std::cout << "Game end" << std::endl;
    //    announcePhase("Game End");
    for (Player* p: context->getPlayers()) {
        p->stopPlaying();
    }
}

void Game::playRound() {
    std::cout << "Round " << numberOfRounds << std::endl;
    context->chooseNextDealer();
    gameRound->playRound(context);
    numberOfRounds++;
}

void Game::announceWinner() {
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

void Game::addPlayer(Player* player) {
    context->addPlayer(player);
}

int Game::getNumberOfPlayers() const {
    return context->getNumberOfPlayers();
}

void Game::join(PlayerController* player) {// TODO: test this method
    Player* newPlayer = new Player(player, INITIAL_AMOUNT_OF_MONEY);
    context->addPlayer(newPlayer);
    sendChatMessage("A new player joined!");
}

void Game::leave(PlayerController* player) {// TODO: test this method
    //players.erase(player);
}

void Game::sendChatMessage(const std::string& msg) {// TODO: test this method
    std::for_each(context->getPlayers().begin(), context->getPlayers().end(),
                  boost::bind(&Player::deliver, _1, boost::ref(msg)));
}

}
