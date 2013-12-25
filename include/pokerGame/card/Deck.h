#ifndef DECK_H
#define DECK_H

#include "pokerGame/card/Card.h"
#include <vector>

namespace pokerGame {
namespace card {

const int DECK_SIZE(52);

class Deck {
public:
    Deck();
    virtual void burn();
    virtual void shuffle();
    virtual Card draw();

    virtual void removeCard(Card card);

    std::vector<std::vector<Card> > toCouples() const;

    int getCount() const;
private:
    void init();

    std::vector<Card> cards;
};

}
}

#endif
