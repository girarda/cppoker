#include "pokerGame/Player.h"

namespace pokerGame
{
Player::Player(IPlayer *playerImpl): playerImpl(playerImpl), hand(), currentState(NOT_PLAYING), money(0), pot(0), name("")
{
}

Player::~Player()
{
    delete playerImpl;
}

void Player::setMoney(float newValue)
{
    money = newValue;
}

void Player::setName(std::string name)
{
    name = name;
}

void Player::startPlaying()
{
    currentState = PLAYING;
}

void Player::fold()
{
    currentState =  FOLDED;
}

void Player::setupForNewTableTurn() {
    currentState = PLAYING;
    clearPot();
}

void Player::clearPot()
{
    pot = 0;
}

bool Player::hasBetterHand(const Player& other) const
{
    return hand > other.hand;
}

float Player::getPot() const
{
    return pot;
}

bool Player::isPlaying() const
{
    return currentState == PLAYING;
}

bool Player::isFolded() const
{
    return currentState == FOLDED;
}

void Player::addCard(const Card& card)
{
    hand.addCard(card);
}

void Player::addToPot(float moneyToAdd)
{
    money -= moneyToAdd;
    pot += moneyToAdd;
}

void Player::winMoney(float gainedMoney)
{
    money += gainedMoney;
}

Decision Player::makeDecision(float minBet)
{
    Decision decision;
    bool decisionIsValid = false;
    while(!decisionIsValid)
    {
        decision = playerImpl->makeDecision(minBet);
        if (decision.choice == FOLD)
        {
            fold();
            decisionIsValid = true;
        }
        else
        {
            float diffToAdd;
            if (decision.choice == CHECK)
                diffToAdd = minBet - pot;
            else
                diffToAdd = decision.bet - pot;
            if (money >= diffToAdd)
            {
                addToPot(diffToAdd);
                decisionIsValid = true;
            }

        }
    }
    return decision;
}

void Player::seeDealer(const Player& dealer)
{
    playerImpl->seeDealer(dealer.name);
}

void Player::seeBigBlind(const Player& player, float bigBlind)
{
    playerImpl->seeBigBlind(player.name, bigBlind);
}

void Player::seeSmallBlind(const Player& player, float smallBlind)
{
    playerImpl->seeSmallBlind(player.name, smallBlind);
}

void Player::seeWinner(const Player& winner)
{
    playerImpl->seeWinner(winner.name);
}

void Player::seeOpponentCards(const Player& opponent)
{
    playerImpl->seeOpponentCards(opponent.name, opponent.hand);
}

void Player::seeOpponentMoney(const Player& opponent)
{
    playerImpl->seeOpponentMoney(opponent.name, opponent.money);
}

void Player::seeCards()
{
    playerImpl->seeCards(hand);
}

void Player::seeMoney()
{
    playerImpl->seeMoney(money);
}

Player::Player(IPlayer *playerImpl, Hand* hand): playerImpl(playerImpl), hand(*hand), currentState(NOT_PLAYING), money(0), pot(0), name("")
{
}

float Player::getMoney() const
{
    return money;
}

void Player::deliver(const std::string& msg)
{
    playerImpl->deliver(msg);
}
}
