#include "include/pokerGame/simulator/PreFlopSimulator.h"
#include "pokerGame/GameContext.h"
#include "playerInterface/bot/SimpleBettingStrategy.h"
#include "playerInterface/BotPlayerController.h"
#include "pokerGame/simulator/GameRoundPreFlopSimulator.h"
#include <iostream>

namespace pokerGame {
namespace simulator {

PreFlopSimulator::PreFlopSimulator() :
    statisticsController(),
    holeCardsEquivalences(),
    deck(new Deck()),
    bettingRound(new BettingRound()),
    gameRoundSimulator(0),
    statistics(),
    percentageOfWinning(){
}

PreFlopSimulator::~PreFlopSimulator() {
    for (std::vector<HoleCardsEquivalence*>::iterator it = holeCardsEquivalences.begin(); it != holeCardsEquivalences.end(); it++) {
        if (*it) {
            delete *it;
        }
    }
    delete deck;
    delete bettingRound;
    delete gameRoundSimulator;
}

void PreFlopSimulator::simulate() {
    generateAllHoleCardsEquivalences();

    GameContext* gameContext = new GameContext(2);
    Player* player1 = new Player(new playerInterface::BotPlayerController(new playerInterface::bot::SimpleBettingStrategy()), 10);
    gameContext->addPlayer(player1);
    gameContext->chooseNextDealer();

    for(int numberOfPlayers = 2; numberOfPlayers <= MAX_NUMBER_OF_PLAYERS; numberOfPlayers++) {
        gameContext->addPlayer(new Player(new playerInterface::BotPlayerController(new playerInterface::bot::SimpleBettingStrategy()), 10));

        for (HoleCardsEquivalence* equivalence: holeCardsEquivalences) {
            statisticsController.reset();
            for (int i = 0; i < NUMBER_OF_SIMULATIONS; i++) {
                deck->shuffle();
                gameRoundSimulator = new GameRoundPreFlopSimulator(deck, bettingRound, equivalence);
                gameRoundSimulator->playRound(gameContext);
                statisticsController.incrementWins(gameRoundSimulator->getWinner());
            }
            double p = (double) statisticsController.getPlayerWins(player1) / 100;
            statistics.addWinningProbability(equivalence, numberOfPlayers, p);
        }
    }
    statistics.save("../preflop_simulation.data");

    delete gameContext;
}

void PreFlopSimulator::generateAllHoleCardsEquivalences() {
    for (int i = 2; i <= 14; i++) {
        for (int j = i; j <= 14; j++) {
            HoleCardsEquivalence* suitedEquivalence = new HoleCardsEquivalence(i,j);
            HoleCardsEquivalence* unsuitedEquivalence = new HoleCardsEquivalence(i,j);
            holeCardsEquivalences.push_back(suitedEquivalence);
            holeCardsEquivalences.push_back(unsuitedEquivalence);
        }
    }
}

const int PreFlopSimulator::MAX_NUMBER_OF_PLAYERS(10);
const int PreFlopSimulator::NUMBER_OF_SIMULATIONS(100);

}
}
