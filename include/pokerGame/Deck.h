#ifndef DECK_H
#define DECK_H

#include "pokerGame/Card.h"
#include <vector>

namespace pokerGame
{

const int DECK_SIZE(52);

class Deck
{
public:
    Deck();
    virtual void burn();
    virtual void shuffle();
    virtual Card draw();

    int getCount() const;
private:
    std::vector<Card> cards;
    int currentPosition;
};

}

#endif
