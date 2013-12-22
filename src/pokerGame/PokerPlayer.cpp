#include "pokerGame/PokerPlayer.h"

namespace pokerGame
{
PokerPlayer::PokerPlayer(PlayerController *aPlayerController, float initialMoney):
    playerController(aPlayerController),
    hole(),
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

void PokerPlayer::setupForNewRound()
{
    currentState = PLAYING;
    clearPot();
}

void PokerPlayer::discardCards() {
    hole.empty();
}

void PokerPlayer::stopPlaying()
{
    currentState = NOT_PLAYING;
    clearPot();
    discardCards();
}

void PokerPlayer::clearPot()
{
    pot = 0;
}

bool PokerPlayer::hasBetterHand(const PokerPlayer& other, std::vector<Card> sharedCards) const //TODO: test this method
{
    Hand hand(hole, sharedCards);
    Hand otherHand(other.hole, sharedCards);
    return hand > otherHand;
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

bool PokerPlayer::lost() const
{
    return currentState == NOT_PLAYING;
}

void PokerPlayer::addCardToHole(const Card& card)
{
    hole.push_back(card);
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

Decision PokerPlayer::makeDecision(float minBet, float bigBlind, std::vector<Card> sharedCards, int numberOfRaises, int numberOfPlayers)
{
    Decision decision;
    bool decisionIsValid = false;
    while(!decisionIsValid)
    {
        float diffToAdd = minBet - pot;;
        decision = playerController->makeDecision(hole, sharedCards, minBet, bigBlind, numberOfRaises, numberOfPlayers);
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
    hole[0].show();
    hole[1].show();
}

std::vector<Card> PokerPlayer::getVisibleHole() const {
    std::vector<Card> visibleHole;
    for (Card c: hole) {
        if(c.isVisible()) {
            visibleHole.push_back(c);
        }
    }
    return visibleHole;
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

void PokerPlayer::seeOpponentHole(const PokerPlayer& opponent)
{
    playerController->seeOpponentHole(opponent.getName(), opponent.getVisibleHole());
}

void PokerPlayer::seeOpponentMoney(const PokerPlayer& opponent)
{
    playerController->seeOpponentMoney(opponent.getName(), opponent.money);
}

void PokerPlayer::seeHole()
{
    playerController->seeHole(hole);
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

float PokerPlayer::getMoney() const
{
    return money;
}

}
