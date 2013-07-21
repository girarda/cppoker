#include "pokerGame/Player.h"
#include "pokerGame/Deck.h"
#include "network/OnlineRoom.h"

namespace pokerGame
{

class GameEngine : public network::OnlineRoom
{
public:
    GameEngine();

    void start();
    void tableTurn();
    void playerTurn(Player* player, float minBet);
    void announcements(const Player* player);

    void preFlop();
    void flop();
    void turn();
    void river();
    void showdown();

    void addPlayer(Player* player);
    void playRound(float minBet);

    float getTotalPot();

    void announceWinner();
    void initTableTurn();
    void betBlinds();

    int getNumberOfPlayers() const;
    int getNumberOfPlayingPlayers() const;

    virtual void join(IPlayer* player);
    virtual void leave(IPlayer* player);
    virtual void deliver(const std::string& mesage);

private:

    Deck deck;
    std::vector<Player*> players;
    int numberTableTurns;
    float bet;
    float bigBlind;
    Player* bigBlindPlayer;
    Player* smallBlindPlayer;
    Player* dealer;
};
}
