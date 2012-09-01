#include "core/Hand.h"
#include "core/Deck.h"
#include <iostream>

void shuffle_test()
{
    std::cout << "Shuffle test" << std::endl; 
    pcore::Deck newDeck;
    newDeck.shuffle();
    for ( int i = 0; i < 52; ++i )
    {
        std::cout <<  newDeck.draw().toString() << std::endl;
    }
}

int main( int argc, char **argv )
{
    shuffle_test();
    return 0;
}
