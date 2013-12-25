#include "playerController/BotPlayerController.h"

namespace playerController {

BotPlayerController::BotPlayerController(bot::BettingStrategy* botBettingStrategy) : bettingStrategy(botBettingStrategy) {
}

BotPlayerController::~BotPlayerController() {
    if (bettingStrategy) {
        delete bettingStrategy;
    }
}

pokerGame::Decision BotPlayerController::makeDecision(std::vector<pokerGame::card::Card> hole, std::vector<pokerGame::card::Card> sharedCards, float minBet, float bigBlind, pokerGame::modeling::BettingContext* bettingContext, std::vector<pokerGame::modeling::OpponentModel> opponents) {
    return bettingStrategy->makeDecision(hole, sharedCards, minBet, bigBlind, bettingContext, opponents);
}

void BotPlayerController::seeDealer(std::string dealer) {
}

void BotPlayerController::seeBigBlind(std::string player, float bigBlind) {
}

void BotPlayerController::seeSmallBlind(std::string player, float smallBlind) {
}

void BotPlayerController::seeWinner(std::string winner) {
}

void BotPlayerController::seeOpponentHole(std::string opponent, const pokerGame::card::Hand& hand) {
}

void BotPlayerController::seeOpponentMoney(std::string opponent, float money) {
}

void BotPlayerController::seeHole(std::vector<pokerGame::card::Card> hole) {
}

void BotPlayerController::seeMoney(float money) {
}

void BotPlayerController::seePlayerTurn(std::string player) {
}

void BotPlayerController::seeGamePhase(std::string phaseName) {
}

void BotPlayerController::seeRoundWinner(std::string winner, float moneyWon) {
}

void BotPlayerController::deliver(const std::string& message) {
}

}
