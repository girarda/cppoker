#ifndef STATISTICSCONTROLLER_H
#define STATISTICSCONTROLLER_H

#include "pokerGame/PlayerController.h"
#include "pokerGame/Player.h"
#include <map>

namespace pokerGame {
namespace simulator {

class WinningStatistics {
public:
    WinningStatistics();

    void reset();

    void incrementWins(Player* winner);

    int getPlayerWins(Player* player);

private:
    std::map<Player*, int> wins;
};

#endif
}
}
