#include "pokerGame/Player.h"

namespace pokerGame
{
Player::Player(PlayerController *aPlayerController, float initialMoney):
    playerController(aPlayerController),
    hole(),
    currentState(NOT_PLAYING),
    money(initialMoney),
    pot(0)
{
}

Player::~Player()
{
    if (playerController)
    {
        delete playerController;
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

void Player::setupForNewRound()
{
    currentState = PLAYING;
    clearPot();
}

void Player::discardCards() {
    hole.empty();
}

void Player::stopPlaying()
{
    currentState = NOT_PLAYING;
    clearPot();
    discardCards();
}

void Player::clearPot()
{
    pot = 0;
}

bool Player::hasBetterHand(const Player& other, std::vector<Card> sharedCards) const //TODO: test this method
{
    Hand hand(hole, sharedCards);
    Hand otherHand(other.hole, sharedCards);
    return hand > otherHand;
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

bool Player::lost() const
{
    return currentState == NOT_PLAYING;
}

void Player::addCardToHole(const Card& card)
{
    hole.push_back(card);
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

Decision Player::makeDecision(float minBet, float bigBlind, std::vector<Card> sharedCards, int numberOfRaises, int numberOfPlayers)
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

void Player::showCards()
{
    hole[0].show();
    hole[1].show();
}

std::vector<Card> Player::getVisibleHole() const {
    std::vector<Card> visibleHole;
    for (Card c: hole) {
        if(c.isVisible()) {
            visibleHole.push_back(c);
        }
    }
    return visibleHole;
}

void Player::seeGamePhase(std::string phaseName)
{
    playerController->seeGamePhase(phaseName);
}

void Player::seePlayerTurn(const Player& player)
{
    playerController->seePlayerTurn(player.getName());
}

void Player::seeDealer(const Player& dealer)
{
    playerController->seeDealer(dealer.getName());
}

void Player::seeBigBlind(const Player& player, float bigBlind)
{
    playerController->seeBigBlind(player.getName(), bigBlind);
}

void Player::seeSmallBlind(const Player& player, float smallBlind)
{
    playerController->seeSmallBlind(player.getName(), smallBlind);
}

void Player::seeRoundWinner(const Player& winner, float moneyWon)
{
    playerController->seeRoundWinner(winner.getName(), moneyWon);
}

void Player::seeWinner(const Player& winner)
{
    playerController->seeWinner(winner.getName());
}

void Player::seeOpponentHole(const Player& opponent)
{
    playerController->seeOpponentHole(opponent.getName(), opponent.getVisibleHole());
}

void Player::seeOpponentMoney(const Player& opponent)
{
    playerController->seeOpponentMoney(opponent.getName(), opponent.money);
}

void Player::seeHole()
{
    playerController->seeHole(hole);
}

void Player::seeMoney()
{
    playerController->seeMoney(money);
}

std::string Player::getName() const
{
    return playerController->getName();
}

void Player::deliver(const std::string& msg)
{
    playerController->deliver(msg);
}

float Player::getMoney() const
{
    return money;
}

}
