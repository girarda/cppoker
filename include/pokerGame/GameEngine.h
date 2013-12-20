#include "pokerGame/PokerPlayer.h"
#include "pokerGame/Deck.h"
#include "network/OnlineRoom.h"
#include "GameRound.h"

namespace pokerGame
{

class GameEngine : public network::OnlineRoom
{
public:
    GameEngine(GameRound* gameRoundToUse);
    virtual ~GameEngine();

    void start();
    void endGame();
    void exit();

    void playRound();

    void addPlayer(PokerPlayer* player);

    float getTotalPot() const;

    void announceWinner();

    int getNumberOfPlayers() const;
    int getNumberOfPlayingPlayers() const;

    virtual void join(PlayerController* player);
    virtual void leave(PlayerController* player);
    virtual void sendChatMessage(const std::string& mesage);

private:
    void chooseNextDealer();

    std::vector<PokerPlayer*> players;
    int numberOfRounds;
    float bet;
    float bigBlind;
    int bigBlindPlayerIndex;
    int smallBlindPlayerIndex;
    int dealerIndex;

    GameRound* gameRound;

    const float INITIAL_AMOUNT_OF_MONEY;
};
}

