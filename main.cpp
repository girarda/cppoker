#include <iostream>
#include <ctime>
#include <exception>
#include "network/Server.h"
#include "network/OnlineRoom.h"
#include "pokerGame/GameEngine.h"
#include "pokerGame/GameContext.h"
#include "pokerGame/GameRound.h"
#include "pokerGame/Deck.h"
#include "pokerGame/BettingRound.h"
#include "playerInterface/BotPlayerController.h"
#include "playerInterface/bot/SimpleBettingStrategy.h"
#include "playerInterface/bot/ProbabilisticBettingStrategy.h"
#include "pokerGame/HandStrengthEvaluator.h"
#include "pokerGame/simulator/PreFlopSimulator.h"

#include "boost/thread/thread.hpp"

void initRandom();

void runServer() {
    pokerGame::GameContext* gameContext = new pokerGame::GameContext(2);
    pokerGame::Deck* deckToUse = new pokerGame::Deck();
    pokerGame::BettingRound* bettingRoundToUse = new pokerGame::BettingRound();
    pokerGame::GameRound* gameRoundToUse = new pokerGame::GameRound(deckToUse, bettingRoundToUse);


    pokerGame::GameEngine* room = new pokerGame::GameEngine(gameContext, gameRoundToUse);
        network::Server ts((network::OnlineRoom*) room);
        ts.initService(); //function does not return.
        while (true) {
            boost::this_thread::sleep(boost::posix_time::millisec(1000));
            if (room->getNumberOfPlayers() == 2)
                room->start();
        }

}

void runBotSimulation() {

    pokerGame::GameContext* gameContext = new pokerGame::GameContext(2);
    pokerGame::Deck* deckToUse = new pokerGame::Deck();
    pokerGame::BettingRound* bettingRoundToUse = new pokerGame::BettingRound();
    pokerGame::GameRound* gameRoundToUse = new pokerGame::GameRound(deckToUse, bettingRoundToUse);


    pokerGame::GameEngine* room = new pokerGame::GameEngine(gameContext, gameRoundToUse);

    pokerGame::simulator::PreFlopStatistics* preFlopStatistics = new pokerGame::simulator::PreFlopStatistics();


    playerInterface::bot::BettingStrategy* sbs1 = new playerInterface::bot::SimpleBettingStrategy();
    pokerGame::HandStrengthEvaluator* handStrengthEvaluator = new pokerGame::HandStrengthEvaluator();
    playerInterface::bot::ProbabilisticBettingStrategy* sbs2 = new playerInterface::bot::ProbabilisticBettingStrategy(handStrengthEvaluator, preFlopStatistics);
    playerInterface::bot::ProbabilisticBettingStrategy* sbs3 = new playerInterface::bot::ProbabilisticBettingStrategy(handStrengthEvaluator, preFlopStatistics);


    std::string n1("bot1");
    std::string n2("bot2");
    playerInterface::BotPlayerController* botCtrl1 = new playerInterface::BotPlayerController(sbs1);
    playerInterface::BotPlayerController* botCtrl2 = new playerInterface::BotPlayerController(sbs2);
    playerInterface::BotPlayerController* botCtrl3 = new playerInterface::BotPlayerController(sbs3);

    pokerGame::Player* bot1 = new pokerGame::Player(botCtrl1,10);
    pokerGame::Player* bot2 = new pokerGame::Player(botCtrl2,10);
    pokerGame::Player* bot3 = new pokerGame::Player(botCtrl3,10);

    room->addPlayer(bot1);
    room->addPlayer(bot2);
    room->start();

    delete gameContext;
    delete deckToUse;
    delete bettingRoundToUse;
    delete gameRoundToUse;
    delete room;
    delete handStrengthEvaluator;
    delete preFlopStatistics;
}

void runPreFlopSimulation() {
    pokerGame::simulator::PreFlopSimulator simulator;
    simulator.simulate();
}

int main(int argc, char** argv) {

    initRandom();
    runPreFlopSimulation();
    //runBotSimulation();
    return 0;
}

/* This function is critical for RNG */
void initRandom()
{
    std::srand(time(nullptr));
}

