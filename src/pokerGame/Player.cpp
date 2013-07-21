#include "pokerGame/Player.h"

namespace pokerGame
{
Player::Player(IPlayer *playerImpl): mPlayer(playerImpl), mHand(), mCurrentState(NOT_PLAYING), mMoney(0), mPot(0), mName("")
{
}

void Player::setMoney(float newValue)
{
    mMoney = newValue;
}

void Player::setName(std::string name)
{
    mName = name;
}

void Player::startPlaying()
{
    mCurrentState = PLAYING;
}

void Player::fold()
{
    mCurrentState =  FOLDED;
}

void Player::setupForNewTableTurn() {
    mCurrentState = PLAYING;
    clearPot();
}

void Player::clearPot()
{
    mPot = 0;
}

bool Player::hasBetterHand(const Player& other) const
{
    return mHand > other.mHand;
}

float Player::getPot() const
{
    return mPot;
}

bool Player::isPlaying() const
{
    return mCurrentState == PLAYING;
}

bool Player::isFolded() const
{
    return mCurrentState == FOLDED;
}

void Player::addCard(const Card& card)
{
    mHand.addCard(card);
}

void Player::addToPot(float moneyToAdd)
{
    mMoney -= moneyToAdd;
    mPot += moneyToAdd;
}

void Player::winMoney(float gainedMoney)
{
    mMoney += gainedMoney;
}

Decision Player::makeDecision(float minBet)
{
    Decision decision;
    bool decisionIsValid = false;
    while(!decisionIsValid)
    {
        decision = mPlayer->makeDecision(minBet);
        if (decision.choice == FOLD)
        {
            fold();
            decisionIsValid = true;
        }
        else
        {
            float diffToAdd;
            if (decision.choice == CHECK)
                diffToAdd = minBet - mPot;
            else
                diffToAdd = decision.bet - mPot;
            if (mMoney >= diffToAdd)
            {
                addToPot(diffToAdd);
                decisionIsValid = true;
            }

        }
    }
    return decision;
}

void Player::seeDealer(const Player& dealer) const
{
    mPlayer->seeDealer(dealer.mName);
}

void Player::seeBigBlind(const Player& player, float bigBlind) const
{
    mPlayer->seeBigBlind(player.mName, bigBlind);
}

void Player::seeSmallBlind(const Player& player, float smallBlind) const
{
    mPlayer->seeSmallBlind(player.mName, smallBlind);
}

void Player::seeWinner(const Player& winner) const
{
    mPlayer->seeWinner(winner.mName);
}

void Player::seeOpponentCards(const Player& opponent) const
{
    mPlayer->seeOpponentCards(opponent.mName, opponent.mHand);
}

void Player::seeOpponentMoney(const Player& opponent) const
{
    mPlayer->seeOpponentMoney(opponent.mName, opponent.mMoney);
}

void Player::seeCards() const
{
    mPlayer->seeCards(mHand);
}

void Player::seeMoney() const
{
    mPlayer->seeMoney(mMoney);
}

Player::Player(IPlayer *playerImpl, Hand* hand): mPlayer(playerImpl), mHand(*hand), mCurrentState(NOT_PLAYING), mMoney(0), mPot(0), mName("")
{
}

float Player::getMoney() const
{
    return mMoney;
}

void Player::deliver(const std::string& msg)
{
    mPlayer->deliver(msg);
}
}
