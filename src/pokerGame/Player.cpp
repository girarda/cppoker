#include "pokerGame/Player.h"

namespace pokerGame
{
Player::Player(IPlayer *playerImpl, float initialMoney):
    playerImpl(playerImpl),
    hand(),
    currentState(NOT_PLAYING),
    money(initialMoney),
    pot(0)
{
}

Player::~Player()
{
    if (playerImpl)
    {
        delete playerImpl;
    }
}

void Player::setMoney(float newValue)
{
    money = newValue;
}

void Player::startPlaying()
{
    currentState = PLAYING;
}

void Player::fold()
{
    currentState =  FOLDED;
}

void Player::setupForNewTableTurn()
{
    currentState = PLAYING;
    clearPot();
    hand.empty();
}

void Player::stopPlaying()
{
    currentState = NOT_PLAYING;
    clearPot();
    hand.empty();
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

void Player::showCards()
{
    hand.showCards();
}

void Player::seeDealer(const Player& dealer)
{
    playerImpl->seeDealer(dealer.getName());
}

void Player::seeBigBlind(const Player& player, float bigBlind)
{
    playerImpl->seeBigBlind(player.getName(), bigBlind);
}

void Player::seeSmallBlind(const Player& player, float smallBlind)
{
    playerImpl->seeSmallBlind(player.getName(), smallBlind);
}

void Player::seeRoundWinner(const Player& winner)
{
    playerImpl->seeRoundWinner(winner.getName());
}

void Player::seeWinner(const Player& winner)
{
    playerImpl->seeWinner(winner.getName());
}

void Player::seeOpponentCards(const Player& opponent)
{
    playerImpl->seeOpponentCards(opponent.getName(), opponent.hand.getVisibleHand());
}

void Player::seeOpponentMoney(const Player& opponent)
{
    playerImpl->seeOpponentMoney(opponent.getName(), opponent.money);
}

void Player::seeCards()
{
    playerImpl->seeCards(hand);
}

void Player::seeMoney()
{
    playerImpl->seeMoney(money);
}

std::string Player::getName() const
{
    return playerImpl->getName();
}

void Player::deliver(const std::string& msg)
{
    playerImpl->deliver(msg);
}

Player::Player(IPlayer *playerImpl, float initialMoney, Hand* hand): playerImpl(playerImpl), hand(*hand), currentState(NOT_PLAYING), money(initialMoney), pot(0)
{
}

float Player::getMoney() const
{
    return money;
}

}
