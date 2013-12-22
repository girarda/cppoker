#include "include/pokerGame/BettingRound.h"
#include <iostream>

namespace pokerGame {

BettingRound::BettingRound() : gameContext(0), sharedCards(), numberOfRaises(0) {
}

void BettingRound::start(GameContext* gameContext, std::vector<Card> sharedCards) {
    initialize(gameContext, sharedCards);

    bool entirePass = false;

    do {
        gameContext->nextPlayer();
        if (gameContext->getCurrentPlayerIndex() == gameContext->getDealerIndex()) {
            entirePass = true;
        }
        playerTurn(gameContext->getCurrentPlayer());


    } while (!(entirePass && allPotsAreEven()));
}

void BettingRound::initialize(GameContext* gameContext, std::vector<Card> sharedCards) {
    this->gameContext = gameContext;
    this->sharedCards = sharedCards;
    this->gameContext->setCurrentPlayerDealer();
}

void BettingRound::playerTurn(Player* player) {
    announcePlayerTurn(player);
    announcements(player);
    if(player->isPlaying()) {
        Decision d = player->makeDecision(getCurrentMinimumBid(), gameContext->getBigBlind(), sharedCards, numberOfRaises, gameContext->getPlayers().size());
        if (d.choice == pokerGame::RAISE) {
            numberOfRaises++;
        }
    }
}

void BettingRound::announcePlayerTurn(Player* player) {
    for (Player* p: gameContext->getPlayers()) {
        p->seePlayerTurn(*player);
    }
}

void BettingRound::announcements(Player* player) {
    player->seeDealer(*gameContext->getPlayers()[gameContext->getDealerIndex()]);
    player->seeBigBlind(*gameContext->getPlayers()[gameContext->getBigBlindIndex()], gameContext->getBigBlind());
}

float BettingRound::getCurrentMinimumBid() const {
    float maxBid = gameContext->getBigBlind();
    for(Player* p: gameContext->getPlayers()) {
        if (p->getPot() > maxBid) {
            maxBid = p->getPot();
        }
    }
    return maxBid;
}

bool BettingRound::allPotsAreEven() const {
    bool first = true;
    float pot;
    for (Player* player: gameContext->getPlayers()) {
        if (player->isPlaying() && !player->isAllIn()) {
            if (first) {
                pot = player->getPot();
                first = false;
            } else {
                if (player->getPot() != pot && !player->isAllIn()) {
                    return false;
                }
            }
        }
    }
    return true;
}

}
