#ifndef STATISTICSCONTROLLER_H
#define STATISTICSCONTROLLER_H

#include "pokerGame/PlayerController.h"
#include "pokerGame/Player.h"
#include <map>

namespace pokerGame {
namespace simulator {

class StatisticsController {
public:
    StatisticsController();

    void initializeStatistics();

    void storeWinner(Player* winner);

    int getPlayerWins(Player* player);

private:
    std::map<Player*, int> wins;
};

#endif
}
}
