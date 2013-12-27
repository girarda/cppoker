#include "pokerGame/Player.h"
#include "pokerGame/card/Deck.h"
#include "network/OnlineRoom.h"
#include "GameRound.h"
#include "GameContext.h"

namespace pokerGame {

class Game : public network::OnlineRoom {
public:
    Game(GameContext* context, GameRound* gameRoundToUse);
    virtual ~Game();

    void start();
    void endGame();
    void exit();

    void playRound();

    void addPlayer(Player* player);

    float getTotalPot() const;

    void announceWinner();

    int getNumberOfPlayers() const;

    virtual void join(PlayerController* player);
    virtual void leave(PlayerController* player);
    virtual void sendChatMessage(std::string mesage);

private:
    void chooseNextDealer();

    GameContext* context;
    int numberOfRounds;

    GameRound* gameRound;

    const float INITIAL_AMOUNT_OF_MONEY;
};
}

