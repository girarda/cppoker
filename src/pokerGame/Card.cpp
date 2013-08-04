#include "pokerGame/Card.h"
#include <assert.h>
#include <sstream>

namespace pokerGame
{
Card::Card(int rank, int suit): rank(rank), suit(suit), visible(true)
{
    assert(rank <= pokerGame::MAX_RANK && rank >= pokerGame::MIN_RANK);
    assert(suit <= pokerGame::MAX_SUIT && suit >= pokerGame::MIN_SUIT);
}

int Card::getRank() const
{
    return rank;
}

int Card::getSuit() const
{
    return suit;
}

bool Card::isSameSuit(const Card &other) const
{
    return suit == other.suit;
}

bool Card::isVisible() const
{
    return visible;
}

void Card::show()
{
    visible = true;
}

void Card::hide()
{
    visible = false;
}

std::string Card::toString() const
{
    std::stringstream ss;
    ss << rank;
    std::string retval;
    if (rank < 11)
        retval = ss.str();
    else if (rank == 11)
        retval = "J";
    else if (rank == 12)
        retval = "Q";
    else if (rank == 13)
        retval = "K";
    else if (rank == 14)
        retval = "A";

    switch(suit)
    {
    case (DIAMOND):
        retval += "D";
        break;
    case (HEART):
        retval += "H";
        break;
    case (CLUB):
        retval += "C";
        break;
    case (SPADE):
        retval += "S";
        break;
    default:
        retval+="Error";
    }

    return retval;
}

}
