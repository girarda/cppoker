#include "include/pokerGame/simulator/StatisticsController.h"

namespace pokerGame {
namespace simulator {

StatisticsController::StatisticsController() : wins()
{
}

void StatisticsController::reset() {
    wins.clear();
}

void StatisticsController::incrementWins(Player* winner) {
    wins[winner]++;
}

int StatisticsController::getPlayerWins(Player* player) {
    return wins[player];
}

}
}
