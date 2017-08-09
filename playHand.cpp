#include <iostream>
#include <cassert>

#include "Card.h"
#include "Deck.h"
#include "Hand.h"

#include "playBlackjack.h"
#include "Strategy.h"

Hand& playHand(Deck &deck, Hand &playerHand, Hand &dealerHand)
{
	assert(deck.getNumDecks() > 0 &&
           "playHand() requires at least one deck in play");
	assert(playerHand.getNumCards() >= 2 &&
		"playHand() requires a player hand with at least two cards");

	while (true)
	{
		// Check if the player busted
		if (playerHand.getHandValue() > 21)
		{
            // Change its value to one if this is the case
            playerHand.changeAce(playerHand.checkAces());
            // Check if the player still busted
            if (playerHand.getHandValue() > 21)
                return playerHand; // The player busted - return the hand
		}

		// Get the choice of whether to hit or stand
		char choice{ getStrategyChoice(deck, playerHand, dealerHand) };
		assert((choice == 'h' || choice == 's') && "The choice must be either h or s");
		if (choice == 'h')
			playerHand += deck.dealCard(); // The player hit - deal another card
		else
			return playerHand; // The player stands - return the hand
	}
}
