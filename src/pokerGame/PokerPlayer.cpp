#include "pokerGame/PokerPlayer.h"

namespace pokerGame
{
PokerPlayer::PokerPlayer(Player *playerImpl, float initialMoney):
    playerImpl(playerImpl),
    hand(),
    currentState(NOT_PLAYING),
    money(initialMoney),
    pot(0)
{
}

PokerPlayer::~PokerPlayer()
{
    if (playerImpl)
    {
        delete playerImpl;
    }
}

void PokerPlayer::setMoney(float newValue)
{
    money = newValue;
}

void PokerPlayer::startPlaying()
{
    currentState = PLAYING;
}

void PokerPlayer::fold()
{
    currentState =  FOLDED;
}

void PokerPlayer::setupForNewTableTurn()
{
    currentState = PLAYING;
    clearPot();
    hand.empty();
}

void PokerPlayer::stopPlaying()
{
    currentState = NOT_PLAYING;
    clearPot();
    hand.empty();
}

void PokerPlayer::clearPot()
{
    pot = 0;
}

bool PokerPlayer::hasBetterHand(const PokerPlayer& other) const
{
    return hand > other.hand;
}

float PokerPlayer::getPot() const
{
    return pot;
}

bool PokerPlayer::isPlaying() const
{
    return currentState == PLAYING;
}

bool PokerPlayer::isFolded() const
{
    return currentState == FOLDED;
}

void PokerPlayer::addCard(const Card& card)
{
    hand.addCard(card);
}

void PokerPlayer::addToPot(float moneyToAdd)
{
    money -= moneyToAdd;
    pot += moneyToAdd;
}

void PokerPlayer::winMoney(float gainedMoney)
{
    money += gainedMoney;
}

Decision PokerPlayer::makeDecision(float minBet)
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

void PokerPlayer::showCards()
{
    hand.showCards();
}

void PokerPlayer::seeGamePhase(const std::string& phaseName)
{
    playerImpl->seeGamePhase(phaseName);
}

void PokerPlayer::seePlayerTurn(const PokerPlayer& player)
{
    playerImpl->seePlayerTurn(player.getName());
}

void PokerPlayer::seeDealer(const PokerPlayer& dealer)
{
    playerImpl->seeDealer(dealer.getName());
}

void PokerPlayer::seeBigBlind(const PokerPlayer& player, float bigBlind)
{
    playerImpl->seeBigBlind(player.getName(), bigBlind);
}

void PokerPlayer::seeSmallBlind(const PokerPlayer& player, float smallBlind)
{
    playerImpl->seeSmallBlind(player.getName(), smallBlind);
}

void PokerPlayer::seeRoundWinner(const PokerPlayer& winner, float moneyWon)
{
    playerImpl->seeRoundWinner(winner.getName(), moneyWon);
}

void PokerPlayer::seeWinner(const PokerPlayer& winner)
{
    playerImpl->seeWinner(winner.getName());
}

void PokerPlayer::seeOpponentCards(const PokerPlayer& opponent)
{
    playerImpl->seeOpponentCards(opponent.getName(), opponent.hand.getVisibleHand());
}

void PokerPlayer::seeOpponentMoney(const PokerPlayer& opponent)
{
    playerImpl->seeOpponentMoney(opponent.getName(), opponent.money);
}

void PokerPlayer::seeCards()
{
    playerImpl->seeCards(hand);
}

void PokerPlayer::seeMoney()
{
    playerImpl->seeMoney(money);
}

std::string PokerPlayer::getName() const
{
    return playerImpl->getName();
}

void PokerPlayer::deliver(const std::string& msg)
{
    playerImpl->deliver(msg);
}

PokerPlayer::PokerPlayer(Player *playerImpl, float initialMoney, Hand* hand): playerImpl(playerImpl), hand(*hand), currentState(NOT_PLAYING), money(initialMoney), pot(0)
{
}

float PokerPlayer::getMoney() const
{
    return money;
}

}
