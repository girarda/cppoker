#include "pokerGame/GameContext.h"

namespace pokerGame {

GameContext::GameContext(float initialBigBlind) :
    bigBlind(initialBigBlind), dealerIndex(-1),
    bigBlindIndex(-1),
    smallBlindIndex(-1),
    players(),
    currentPlayerIndex(dealerIndex),
    handContexts() {
}

GameContext::~GameContext() {
    for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); it++) {
        if (*it) {
            delete *it;
        }
    }
}

void GameContext::addPlayer(Player* player) {
    players.push_back(player);
}

void GameContext::removePlayer(int index) {
    players.erase(players.begin() + index);
}

void GameContext::doubleBigBlind() {
    bigBlind *= 2;
}

void GameContext::chooseNextDealer() {
    dealerIndex = getNextPlayingPlayer(dealerIndex);
    bigBlindIndex = getNextPlayingPlayer(dealerIndex);
    smallBlindIndex = getNextPlayingPlayer(bigBlindIndex);
}

int GameContext::getNumberOfPlayers() const {
    return players.size();
}

int GameContext::getNumberOfPlayingPlayers() const
{
    int count = 0;
    for (Player* p: players) {
        if(p->getMoney() != 0) {
            count++;
        }
    }
    return count;
}

int GameContext::getDealerIndex() const {
    return dealerIndex;
}

int GameContext::getBigBlindIndex() const {
    return bigBlindIndex;
}

int GameContext::getSmallBlindIndex() const {
    return smallBlindIndex;
}

int GameContext::getCurrentPlayerIndex() const {
    return currentPlayerIndex;
}

float GameContext::getBigBlind() const {
    return bigBlind;
}

float GameContext::getSmallBlind() const {
    return bigBlind/2;
}

std::vector<Player*> GameContext::getPlayers() const {
    return players;
}

Player* GameContext::getCurrentPlayer() {
    return players[currentPlayerIndex];
}

void GameContext::setDealerIndex(int index) {
    dealerIndex = index;
}

void GameContext::setBigBlindIndex(int index) {
    bigBlindIndex = index;
}

void GameContext::setSmallBlindIndex(int index) {
    smallBlindIndex = index;
}

void GameContext::setCurrentPlayerDealer() {
    currentPlayerIndex = dealerIndex;
}

void GameContext::nextPlayer() {
    currentPlayerIndex++;
    if (currentPlayerIndex == players.size()) {
        currentPlayerIndex = 0;
    }
    currentPlayerIndex = getNextPlayingPlayer(currentPlayerIndex);

}

int GameContext::getNextPlayingPlayer(int player) {
    int tmp;
    for (tmp = player; tmp < players.size(); tmp++) {
        if (players[tmp]->isPlaying()) {
            return tmp;
        }
    }
    for (tmp = 0; tmp < player; tmp++) {
        if (players[tmp]->isPlaying()) {
            return tmp;
        }
    }
}

void GameContext::addHandContext(Player* player, const std::vector<modeling::ActionContext> &actions, double handStrength) {
    for(std::vector<modeling::ActionContext>::const_iterator it = actions.begin(); it != actions.end(); it++) {
        handContexts[player].push_back(modeling::HandContext(*it, handStrength));
    }
}

std::vector<modeling::OpponentModel> GameContext::getCurrentOpponentModels(const std::map<Player*, modeling::ActionContext> &actionContexts) const {
    std::vector<modeling::OpponentModel> opponents;
    for (std::map<Player*, std::vector<modeling::HandContext> >::const_iterator it = handContexts.begin(); it != handContexts.end(); it++) {
        if (it->first->isPlaying()) {
            modeling::OpponentModel op(actionContexts.find(it->first)->second, it->second);
            opponents.push_back(op);
        }
    }
    return opponents;
}

}
