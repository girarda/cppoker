#include "include/pokerGame/simulation/WinningStatistics.h"

namespace pokerGame {
namespace simulation {

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
