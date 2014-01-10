#include <iostream>
#include <ctime>
#include <exception>
#include "network/Server.h"
#include "network/OnlineRoom.h"
#include "pokerGame/Game.h"
#include "pokerGame/GameContext.h"
#include "pokerGame/GameRound.h"
#include "pokerGame/card/Deck.h"
#include "pokerGame/BettingRound.h"
#include "playerController//BotPlayerController.h"
#include "playerController/bot/SimpleBettingStrategy.h"
#include "playerController/bot/ProbabilisticBettingStrategy.h"
#include "pokerGame/card/HandStrengthEvaluator.h"
#include "pokerGame/simulation/PreFlopSimulator.h"
#include "playerController/bot/AgressiveBettingStrategy.h"

#include "boost/thread/thread.hpp"

void initRandom();

void runServer() {
    pokerGame::GameContext* gameContext = new pokerGame::GameContext(2);
    pokerGame::card::Deck* deckToUse = new pokerGame::card::Deck();
    pokerGame::BettingRound* bettingRoundToUse = new pokerGame::BettingRound();
    pokerGame::GameRound* gameRoundToUse = new pokerGame::GameRound(deckToUse, bettingRoundToUse);


    pokerGame::Game* room = new pokerGame::Game(gameContext, gameRoundToUse);
        network::Server ts((network::OnlineRoom*) room);
        ts.initService(); //function does not return.
        while (true) {
            boost::this_thread::sleep(boost::posix_time::millisec(1000));
            if (room->getNumberOfPlayers() == 2)
                room->start();
        }
}


void runPreFlopSimulation() {
    pokerGame::simulation::PreFlopSimulator simulator;
    simulator.simulate();
}

int main(int argc, char** argv) {

    initRandom();
    runServer();
    return 0;
}

/* This function is critical for RNG */
void initRandom()
{
    std::srand(time(nullptr));
}

