#include "include/pokerGame/BettingRound.h"
#include <iostream>
#include <utility>

namespace pokerGame {

BettingRound::BettingRound() : gameContext(0), sharedCards(), numberOfRaises(0), bettingActions() {
}

void BettingRound::start(GameContext* gameContext, std::vector<Card> sharedCards, BettingRoundType bettingRoundType) {
    initialize(gameContext, sharedCards, bettingRoundType);

    bool entirePass = false;

    do {
        gameContext->nextPlayer();
        if (gameContext->getCurrentPlayerIndex() == gameContext->getDealerIndex()) {
            entirePass = true;
        }
        playerTurn(gameContext->getCurrentPlayer());


    } while (!(entirePass && allPotsAreEven()));
}

void BettingRound::initialize(GameContext* gameContext, std::vector<Card> sharedCards, BettingRoundType bettingRoundType) {
    this->gameContext = gameContext;
    this->sharedCards = sharedCards;
    this->gameContext->setCurrentPlayerDealer();
    this->bettingRoundType = bettingRoundType;
    this->bettingActions.clear();
}

void BettingRound::playerTurn(Player* player) {
    announcePlayerTurn(player);
    announcements(player);
    if(player->isPlaying()) {
        BettingContext bettingContext(bettingRoundType, numberOfRaises, gameContext->getNumberOfPlayingPlayers());
        Decision d = player->makeDecision(getCurrentMinimumBid(), gameContext->getBigBlind(), sharedCards, &bettingContext, gameContext->getCurrentOpponentModels(bettingActions));
        if (d.choice == pokerGame::RAISE) {
            numberOfRaises++;
        }
        bettingActions.insert(std::make_pair(player, BettingAction(bettingContext, d)));
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

std::map<Player*, BettingAction> BettingRound::getBettingActions() {
    return bettingActions;
}


}
