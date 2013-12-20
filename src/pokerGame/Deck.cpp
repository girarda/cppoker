#include "pokerGame/Deck.h"
#include <assert.h>
#include <algorithm>

namespace pokerGame
{
Deck::Deck() : cards(), currentPosition(DECK_SIZE)
{
    for( int rank(MIN_RANK) ; rank <= MAX_RANK ; rank++ )
    {
        for( int suit(MIN_SUIT) ; suit <= MAX_SUIT ; ++suit )
        {
            cards.push_back(Card(rank,suit));
        }

    }

}

void Deck::burn()
{
    assert (currentPosition > 0);
    --currentPosition;
}

Card Deck::draw()
{
    burn();
    return cards[currentPosition];
}

void Deck::shuffle()
{
    currentPosition = DECK_SIZE;
    std::random_shuffle (cards.begin(), cards.end());
}

int Deck::getCount() const
{
    return currentPosition;
}


}
