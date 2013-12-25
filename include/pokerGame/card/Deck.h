#ifndef DECK_H
#define DECK_H

#include "pokerGame/card/Card.h"
#include <vector>
#include <deque>

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

    std::vector<std::vector<Card> > toCouples();

    int getCount() const;
private:
    void init();

    std::deque<Card> cards;
};

}
}

#endif
