#include "include/pokerGame/simulator/StatisticsController.h"

namespace pokerGame {
namespace simulator {

StatisticsController::StatisticsController() : wins()
{
}

void StatisticsController::initializeStatistics() {
    wins.clear();
}

void StatisticsController::storeWinner(Player* winner) {
    wins[winner]++;
}

int StatisticsController::getPlayerWins(Player* player) {
    return wins[player];
}

}
}
