#include "include/pokerGame/simulator/WinningStatistics.h"

namespace pokerGame {
namespace simulator {

WinningStatistics::WinningStatistics() : wins()
{
}

void WinningStatistics::reset() {
    wins.clear();
}

void WinningStatistics::incrementWins(Player* winner) {
    wins[winner]++;
}

int WinningStatistics::getPlayerWins(Player* player) {
    return wins[player];
}

}
}
