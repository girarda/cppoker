#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "Player.h"
#include "pokerGame/modeling/ActionContext.h"
#include "pokerGame/modeling/HandContext.h"
#include "pokerGame/modeling/OpponentModel.h"
#include <vector>
#include <map>

namespace pokerGame {

class GameContext {
public:
    GameContext(float initialBigBlind);
    virtual ~GameContext();

    void addPlayer(Player* player);
    void removePlayer(int index);

    void doubleBigBlind();

    int getNumberOfPlayers() const;
    int getNumberOfPlayingPlayers() const;

    void chooseNextDealer();
    void nextPlayer();
    void setCurrentPlayerDealer();

    int getDealerIndex() const;
    int getBigBlindIndex() const;
    int getSmallBlindIndex() const;
    int getCurrentPlayerIndex() const;
    float getBigBlind() const;
    float getSmallBlind() const;

    Player* getCurrentPlayer();

    void setDealerIndex(int index);
    void setBigBlindIndex(int index);
    void setSmallBlindIndex(int index);

    std::vector<Player*> getPlayers() const;

    void addHandContext(Player* player, std::vector<modeling::ActionContext>, double handStrength);
    std::vector<modeling::OpponentModel> getCurrentOpponentModels(std::map<Player*, modeling::ActionContext> bettingActions) const;

private:
    int dealerIndex;
    int bigBlindIndex;
    int smallBlindIndex;
    int currentPlayerIndex;
    float bigBlind;
    std::vector<Player*> players;
    std::map<Player*, std::vector<modeling::HandContext> > handContexts;

    int getNextPlayingPlayer(int player);
};

}

#endif
