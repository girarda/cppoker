#include "pokerGame/Player.h"
#include "pokerGame/Deck.h"
#include "network/OnlineRoom.h"

namespace pokerGame
{

class GameEngine : public network::OnlineRoom
{
public:
    GameEngine();
    virtual ~GameEngine();

    void start();
    void playRound();
    void playerTurn(Player* player, float minBet);
    void announcements(Player* player);

    void preFlop();
    void flop();
    void turn();
    void river();
    void showdown();

    void addPlayer(Player* player);
    void tableTurn(float minBet);

    float getTotalPot() const;

    void announceWinner();
    void initRound();
    void betBlinds();

    int getNumberOfPlayers() const;
    int getNumberOfPlayingPlayers() const;

    virtual void join(IPlayer* player);
    virtual void leave(IPlayer* player);
    virtual void sendChatMessage(const std::string& mesage);

private:
    void chooseNextDealer();
    void distributeOneCard();
    void addOneCardToBoard();

    Deck deck;
    std::vector<Player*> players;
    int numberOfRounds;
    float bet;
    float bigBlind;
    int bigBlindPlayerIndex;
    int smallBlindPlayerIndex;
    int dealerIndex;

    const float INITIAL_AMOUNT_OF_MONEY;
};
}

