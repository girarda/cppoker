#include "pokerGame/PokerPlayer.h"

namespace pokerGame
{
PokerPlayer::PokerPlayer(PlayerController *aPlayerController, float initialMoney):
    playerController(aPlayerController),
    hand(),
    currentState(NOT_PLAYING),
    money(initialMoney),
    pot(0)
{
}

PokerPlayer::~PokerPlayer()
{
    if (playerController)
    {
        delete playerController;
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

Decision PokerPlayer::makeDecision(float minBet, float bigBlind)
{
    Decision decision;
    bool decisionIsValid = false;
    while(!decisionIsValid)
    {
        float diffToAdd = minBet - pot;;
        decision = playerController->makeDecision(hand, minBet, bigBlind);
        if (decision.choice == FOLD)
        {
            fold();
            decisionIsValid = true;
        }
        else
        {
            if (decision.choice == CALL)
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

void PokerPlayer::seeGamePhase(std::string phaseName)
{
    playerController->seeGamePhase(phaseName);
}

void PokerPlayer::seePlayerTurn(const PokerPlayer& player)
{
    playerController->seePlayerTurn(player.getName());
}

void PokerPlayer::seeDealer(const PokerPlayer& dealer)
{
    playerController->seeDealer(dealer.getName());
}

void PokerPlayer::seeBigBlind(const PokerPlayer& player, float bigBlind)
{
    playerController->seeBigBlind(player.getName(), bigBlind);
}

void PokerPlayer::seeSmallBlind(const PokerPlayer& player, float smallBlind)
{
    playerController->seeSmallBlind(player.getName(), smallBlind);
}

void PokerPlayer::seeRoundWinner(const PokerPlayer& winner, float moneyWon)
{
    playerController->seeRoundWinner(winner.getName(), moneyWon);
}

void PokerPlayer::seeWinner(const PokerPlayer& winner)
{
    playerController->seeWinner(winner.getName());
}

void PokerPlayer::seeOpponentCards(const PokerPlayer& opponent)
{
    playerController->seeOpponentCards(opponent.getName(), opponent.hand.getVisibleHand());
}

void PokerPlayer::seeOpponentMoney(const PokerPlayer& opponent)
{
    playerController->seeOpponentMoney(opponent.getName(), opponent.money);
}

void PokerPlayer::seeCards()
{
    playerController->seeCards(hand);
}

void PokerPlayer::seeMoney()
{
    playerController->seeMoney(money);
}

std::string PokerPlayer::getName() const
{
    return playerController->getName();
}

void PokerPlayer::deliver(const std::string& msg)
{
    playerController->deliver(msg);
}

PokerPlayer::PokerPlayer(PlayerController *aPlayerController, float initialMoney, Hand* hand): playerController(aPlayerController), hand(*hand), currentState(NOT_PLAYING), money(initialMoney), pot(0)
{
}

float PokerPlayer::getMoney() const
{
    return money;
}

}
