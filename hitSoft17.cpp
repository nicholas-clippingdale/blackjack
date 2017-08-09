#include <cassert>

#include "Deck.h"
#include "Hand.h"

Hand& hitSoft17(Deck &deck, Hand &dealerHand)
{
    assert(dealerHand.getNumCards() >= 2 &&
           "hitSoft17() requires that the dealer's hand contains at least two cards");
    
    // Check if the dealer has a total of seventeen
    if (dealerHand.getHandValue() == 17)
    {
        // Check if the dealer still has an ace valued at eleven
        // Change its value to one if this is the case
        dealerHand.changeAce(dealerHand.checkAces());
    }
    
    return dealerHand;
}
