#include "pokerGame/PokerPlayer.h"
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
    void endGame();
    void exit();

    void playRound();
    void playerTurn(PokerPlayer* player, float minBet);
    void announcements(PokerPlayer* player);

    void preFlop();
    void flop();
    void turn();
    void river();
    void showdown();

    void addPlayer(PokerPlayer* player);
    void tableTurn(float minBet);

    float getTotalPot() const;

    void announcePhase(const std::string& phaseName);
    void announcePlayerTurn(PokerPlayer* player);
    void announceRoundWinner(PokerPlayer* winner, float moneyWon);
    void announceWinner();

    void initRound();
    void betBlinds();

    int getNumberOfPlayers() const;
    int getNumberOfPlayingPlayers() const;

    virtual void join(PlayerController* player);
    virtual void leave(PlayerController* player);
    virtual void sendChatMessage(const std::string& mesage);

private:
    void chooseNextDealer();
    void distributeOneCard();
    void addOneCardToBoard();

    Deck deck;
    std::vector<PokerPlayer*> players;
    int numberOfRounds;
    float bet;
    float bigBlind;
    int bigBlindPlayerIndex;
    int smallBlindPlayerIndex;
    int dealerIndex;

    const float INITIAL_AMOUNT_OF_MONEY;
};
}

