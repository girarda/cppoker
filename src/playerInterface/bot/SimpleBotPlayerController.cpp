#include "playerInterface/bot/SimpleBotPlayerController.h"

namespace playerInterface
{
SimpleBotPlayerController::SimpleBotPlayerController()
{
}

pokerGame::Decision SimpleBotPlayerController::makeDecision(const pokerGame::Hand& hand, float minBet)
{
    if(isPreFlopHand(hand))
    {
        return makePreFlopDecision(hand, minBet);
    }
    else
    {
        return makePostFlopDecision(hand, minBet);
    }
}

pokerGame::Decision SimpleBotPlayerController::makePreFlopDecision(const pokerGame::Hand& hand, float minBet)
{
    pokerGame::Decision decision;
    if(hand.getHandValue().type == pokerGame::HandType::PAIR)
    {
        decision.choice = pokerGame::CALL;
        decision.bet = minBet;
    }
    else if(hand.getSumOfPower() > 16)
    {
        decision.choice = pokerGame::CHECK;
        decision.bet = 0;
    }
    else 
    {
        decision.choice = pokerGame::FOLD;
        decision.bet = 0;
    }
    return decision;
}

pokerGame::Decision SimpleBotPlayerController::makePostFlopDecision(const pokerGame::Hand& hand, float minBet)
{
    pokerGame::Decision decision;
    if(hand.getHandValue().type == pokerGame::HandType::HIGH_CARD)
    {
        if(minBet == 0) 
        {
            decision.choice = pokerGame::CHECK;
            decision.bet = 0;
        }
        else
        {
            decision.choice = pokerGame::FOLD;
            decision.bet = 0;
        }
    }
    else if(hand.getHandValue().type >= pokerGame::STRAIGHT)
    {
        decision.choice = pokerGame::CALL;
        decision.bet = minBet;
    }
    else 
    {
        decision.choice = pokerGame::CHECK;
        decision.bet = 0;
    }
    return decision;
}

bool SimpleBotPlayerController::isPreFlopHand(const pokerGame::Hand& hand) const
{
    return hand.getSize() == 2; 
}

void SimpleBotPlayerController::seeDealer(std::string dealer)
{
}

void SimpleBotPlayerController::seeBigBlind(std::string player, float bigBlind)
{
}

void SimpleBotPlayerController::seeSmallBlind(std::string player, float smallBlind)
{
}

void SimpleBotPlayerController::seeWinner(std::string winner)
{
}

void SimpleBotPlayerController::seeOpponentCards(std::string opponent, const pokerGame::Hand& hand)
{
}

void SimpleBotPlayerController::seeOpponentMoney(std::string opponent, float money)
{
}

void SimpleBotPlayerController::seeCards(const pokerGame::Hand& hand)
{
}

void SimpleBotPlayerController::seeMoney(float money)
{
}

void SimpleBotPlayerController::seePlayerTurn(std::string player)
{
}

void SimpleBotPlayerController::seeGamePhase(std::string phaseName)
{
}

void SimpleBotPlayerController::seeRoundWinner(std::string winner, float moneyWon)
{
}

void SimpleBotPlayerController::deliver(const std::string& message)
{
}

}
