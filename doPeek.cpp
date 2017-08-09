#include <cassert>

#include "Deck.h"
#include "Hand.h"

#include "Strategy.h"

double doPeek(Deck &deck, Hand &playerHand, Hand &dealerHand, bool takeInsurance)
{
    assert(deck.getNumDecks() > 0 &&
           "doPeek() requires at least one deck in play");
	assert(playerHand.getNumCards() == 2 &&
           "doPeek() requires two cards in the player's hand");
	assert(dealerHand.getNumCards() == 2 &&
           "doPeek() requires two cards in the dealer's hand");

	// Retrieve the dealer's top card value to reduce duplication of function calls
	int dealerTopCardValue{ dealerHand.getDealerTopCard().getCardValue() };

	// Check if the dealer shows an ace or ten
	if (dealerTopCardValue == 10 || dealerTopCardValue == 11)
	{
		// Check if the player can take insurance
        // Check if the dealer shows an ace
		if (takeInsurance == true && dealerTopCardValue == 11)
		{
			// Check if the player has a blackjack
            // Check if the player wants even money
			if (playerHand.checkBlackjack() == true && checkInsurance(deck) == true)
			{
				// The same pay-out occurs whether or not the dealer has a blackjack
                dealerHand.doInsurance();
				return 1.0; // Return win
			}
			// The player does not have a blackjack
            // Check if the player wants insurance
			else if (checkInsurance(deck) == true)
			{
				dealerHand.doInsurance();
                if (dealerHand.checkBlackjack() == true)
                {
                    // The player lost their hand but won the insurance bet
                    return 0.0; // Return tie
                }
				else
                {
                    // The dealer did not have a blackjack
                    return 10.0; // Return insurance loss
                }
			}
		}
        
		// The dealer shows an ace or ten
        // Check if the dealer has a blackjack
		if (dealerHand.checkBlackjack() == true)
		{
			// Check if the player has a blackjack as well
			if (playerHand.checkBlackjack() == true)
                // Both the player and the dealer have a blackjack
				return 0.0; // Return tie
			else
                // Only the dealer has a blackjack
				return -1.0; // Return loss
		}
		// The dealer does not have a blackjack
        // Check if the player has a blackjack
		else if (playerHand.checkBlackjack() == true)
            // Only the player has a blackjack
			return 1.5; // Return blackjack win
	}
	// The dealer does not show an ace or ten
    // Check if the player has a blackjack
	else if (playerHand.checkBlackjack() == true)
        // Only the player has a blackjack
		return 1.5; // Return blackjack win

	return 10.0; // Return no significant outcome from the peek
}
