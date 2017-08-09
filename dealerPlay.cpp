#include <iostream>
#include <cassert>

#include "Card.h"
#include "Deck.h"
#include "Hand.h"

#include "playBlackjack.h"

Hand& dealerPlay(Deck &deck, Hand &dealerHand, bool dealerHitSoft17)
{
	assert(deck.getNumDecks() > 0 &&
           "dealerPlay() requires at least one deck in play");
	assert((dealerHand.getNumCards() == 1 || dealerHand.getNumCards() == 2) &&
           "dealerPlay() requires one or two cards in the dealer's hand");

	// If the dealer hasn't peeked, the second card is dealt
	if (dealerHand.getNumCards() == 1)
		dealerHand += deck.dealCard();

    // Check if the dealer hits a soft seventeen
    if (dealerHitSoft17 == true)
        dealerHand = hitSoft17(deck, dealerHand);
    
	// The dealer now plays to at least seventeen
	while (dealerHand.getHandValue() < 17)
	{
        dealerHand += deck.dealCard();
        
        // Check if the dealer hits a soft seventeen
        if (dealerHitSoft17 == true)
            dealerHand = hitSoft17(deck, dealerHand);
        
        // Check if the dealer busted
        if (dealerHand.getHandValue() > 21)
            // Check if the dealer still has an ace valued at eleven
            // Change its value to one if this is the case
            dealerHand.changeAce(dealerHand.checkAces());
    }

    return dealerHand;
}
