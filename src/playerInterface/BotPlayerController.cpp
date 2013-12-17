#include "playerInterface/BotPlayerController.h"

namespace playerInterface
{
BotPlayerController::BotPlayerController(bot::BettingStrategy* botBettingStrategy) : bettingStrategy(botBettingStrategy)
{
}

pokerGame::Decision BotPlayerController::makeDecision(const pokerGame::Hand& hand, float minBet)
{
    return bettingStrategy->makeDecision(hand, minBet);
}

void BotPlayerController::seeDealer(std::string dealer)
{
}

void BotPlayerController::seeBigBlind(std::string player, float bigBlind)
{
}

void BotPlayerController::seeSmallBlind(std::string player, float smallBlind)
{
}

void BotPlayerController::seeWinner(std::string winner)
{
}

void BotPlayerController::seeOpponentCards(std::string opponent, const pokerGame::Hand& hand)
{
}

void BotPlayerController::seeOpponentMoney(std::string opponent, float money)
{
}

void BotPlayerController::seeCards(const pokerGame::Hand& hand)
{
}

void BotPlayerController::seeMoney(float money)
{
}

void BotPlayerController::seePlayerTurn(std::string player)
{
}

void BotPlayerController::seeGamePhase(std::string phaseName)
{
}

void BotPlayerController::seeRoundWinner(std::string winner, float moneyWon)
{
}

void BotPlayerController::deliver(const std::string& message)
{
}

}
