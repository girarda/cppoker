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

void Deck::removeCard(Card card) {
    for(std::vector<Card>::iterator it = cards.begin(); it != cards.end(); ++it) {
        if (*it == card) {
            cards.erase(it);
            break;
        }
    }
}

int Deck::getCount() const
{
    return currentPosition;
}

std::vector<std::vector<Card> > Deck::toCouples() {
    std::vector<std::vector<Card> > couplesOfCards;
    for (int i = 0; i < cards.size(); i++) {
        for (int j = i+1; j < cards.size(); j++) {
            std::vector<Card> couple;
            couple.push_back(cards[i]);
            couple.push_back(cards[j]);
            couplesOfCards.push_back(couple);
        }
    }
    return couplesOfCards;
}


}
