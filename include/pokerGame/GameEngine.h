#include "pokerGame/Player.h"
#include "pokerGame/Deck.h"
#include "network/OnlineRoom.h"
#include "GameRound.h"
#include "GameContext.h"

namespace pokerGame
{

class GameEngine : public network::OnlineRoom
{
public:
    GameEngine(GameContext* context, GameRound* gameRoundToUse);
    virtual ~GameEngine();

    void start();
    void endGame();
    void exit();

    void playRound();

    void addPlayer(Player* player);

    float getTotalPot() const;

    void announceWinner();

    int getNumberOfPlayers() const;
    int getNumberOfPlayingPlayers() const;

    virtual void join(PlayerController* player);
    virtual void leave(PlayerController* player);
    virtual void sendChatMessage(const std::string& mesage);

private:
    void chooseNextDealer();

    GameContext* context;
    int numberOfRounds;

    GameRound* gameRound;

    const float INITIAL_AMOUNT_OF_MONEY;
};
}

