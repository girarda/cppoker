#include "pokerGame/Player.h"

namespace pokerGame {

Player::Player(PlayerController *aPlayerController, float initialMoney):
    playerController(aPlayerController),
    holeCards(),
    currentState(NOT_PLAYING),
    money(initialMoney),
    pot(0) {
}

Player::~Player() {
    if (playerController) {
        delete playerController;
    }
}

void Player::setMoney(float newValue) {
    money = newValue;
}

void Player::startPlaying() {
    currentState = PLAYING;
}

void Player::fold() {
    currentState =  FOLDED;
}

void Player::setupForNewRound() {
    currentState = PLAYING;
    clearPot();
    discardCards();
}

void Player::discardCards() {
    holeCards.clear();
}

void Player::stopPlaying() {
    currentState = NOT_PLAYING;
    clearPot();
    discardCards();
}

void Player::clearPot() {
    pot = 0;
}

bool Player::hasBetterHand(const Player& other, std::vector<card::Card> sharedCards) const {//TODO: test this method
    card::Hand hand(holeCards, sharedCards);
    card::Hand otherHand(other.holeCards, sharedCards);
    return hand > otherHand;
}

float Player::getPot() const {
    return pot;
}

bool Player::isPlaying() const {
    return currentState == PLAYING;
}

bool Player::isFolded() const {
    return currentState == FOLDED;
}

bool Player::lost() const {
    return currentState == NOT_PLAYING;
}

bool Player::isAllIn() const {
    return isPlaying() && getMoney() == 0;
}

void Player::addCardToHole(card::Card card) {
    if (holeCards.empty()) {
        card.hide();
    }
    holeCards.push_back(card);
}

void Player::addToPot(float moneyToAdd) {
    if (money < moneyToAdd) {
        pot += money;
        money = 0;
    } else {
        money -= moneyToAdd;
        pot += moneyToAdd;
    }
}

void Player::winMoney(float gainedMoney) {
    money += gainedMoney;
}

Decision Player::makeDecision(float minBet, float bigBlind, std::vector<card::Card> sharedCards, modeling::BettingContext* bettingContext, std::vector<modeling::OpponentModel> opponents) {

    float diffToAdd = minBet - pot;;
    Decision decision = playerController->makeDecision(holeCards, sharedCards, minBet, bigBlind, bettingContext, opponents);
    if (decision.choice == FOLD) {
        fold();
    } else if (decision.choice == CALL) {
        if (money >= diffToAdd) {
            addToPot(diffToAdd);
        } else {
            decision.choice = CALL;
            decision.bet = minBet;
            addToPot(money);
        }
    } else {
        diffToAdd = decision.bet - pot;
        if (money >= diffToAdd) {
            addToPot(diffToAdd);
        } else {
            decision.choice = CALL;
            decision.bet = minBet;
            addToPot(money);
        }
    }
    return decision;
}

void Player::showCards() {
    holeCards[0].show();
    holeCards[1].show();
}

std::vector<card::Card> Player::getVisibleHoleCards() const {
    std::vector<card::Card> visibleHole;
    for (card::Card c: holeCards) {
        if(c.isVisible()) {
            visibleHole.push_back(c);
        }
    }
    return visibleHole;
}

void Player::seeGamePhase(std::string phaseName) {
    playerController->seeGamePhase(phaseName);
}

void Player::seePlayerTurn(const Player& player) {
    playerController->seePlayerTurn(player.getName());
}

void Player::seeDealer(const Player& dealer) {
    playerController->seeDealer(dealer.getName());
}

void Player::seeBigBlind(const Player& player, float bigBlind) {
    playerController->seeBigBlind(player.getName(), bigBlind);
}

void Player::seeSmallBlind(const Player& player, float smallBlind) {
    playerController->seeSmallBlind(player.getName(), smallBlind);
}

void Player::seeRoundWinner(const Player& winner, float moneyWon) {
    playerController->seeRoundWinner(winner.getName(), moneyWon);
}

void Player::seeWinner(const Player& winner) {
    playerController->seeWinner(winner.getName());
}

void Player::seeOpponentHoleCards(const Player& opponent) {
    playerController->seeOpponentHole(opponent.getName(), opponent.getVisibleHoleCards());
}

void Player::seeOpponentMoney(const Player& opponent) {
    playerController->seeOpponentMoney(opponent.getName(), opponent.money);
}

void Player::seeHoleCards() {
    playerController->seeHole(holeCards);
}

void Player::seeMoney() {
    playerController->seeMoney(money);
}

std::string Player::getName() const {
    return playerController->getName();
}

void Player::deliver(const std::string& msg) {
    playerController->deliver(msg);
}

float Player::getMoney() const {
    return money;
}

}
