#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "Player.h"
#include "pokerGame/BettingAction.h"
#include "pokerGame/HandContext.h"
#include "pokerGame/OpponentModel.h"
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

    void addHandContext(Player* player, std::vector<BettingAction>, double handStrength);
    std::vector<OpponentModel> getCurrentOpponentModels(std::map<Player*, BettingAction> bettingActions) const;

private:
    int dealerIndex;
    int bigBlindIndex;
    int smallBlindIndex;
    int currentPlayerIndex;
    float bigBlind;
    std::vector<Player*> players;
    std::map<Player*, std::vector<HandContext> > handContexts;

    int getNextPlayingPlayer(int player);
};

}

#endif
