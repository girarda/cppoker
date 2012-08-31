#include "core/Deck.h"
#include <iostream>

void shuffle_test()
{
    std::cout << "Shuffle test" << std::endl; 
    pcore::Deck newDeck;
    pcore::Card *pCard;
    newDeck.init();
    newDeck.shuffle();
    for ( int i = 0; i < 52; ++i )
    {
        pCard = newDeck.drawCard();
    std::cout << pCard->getRank() << " of " << pCard->getSuit() << std::endl;
    }
}

int main( int argc, char **argv )
{
    shuffle_test();
    return 0;
}
