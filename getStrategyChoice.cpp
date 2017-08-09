#include <iostream>
#include <cassert>

#include "Card.h"
#include "Deck.h"
#include "Hand.h"

#include "Strategy.h"

char getStrategyChoice(Deck &deck, Hand &playerHand, Hand &dealerHand)
{
	assert(deck.getNumDecks() > 0 &&
           "getStrategyChoice() requires at least one deck in play");
	assert(playerHand.getNumCards() >= 2 &&
           "getStrategyChoice() requires a at least two cards in the player's hand");
	assert(dealerHand.getNumCards() >= 1 &&
           "getStrategyChoice() requires at least one card in the dealer's hand");
	assert(playerHand.getHandValue() > 2 && playerHand.getHandValue() <= 21 &&
		"getStrategyChoice() requires a player's hand to have a total value betwwen two and twenty one");

	// Check for a soft total
	if (playerHand.getNumCards() == 2 && playerHand.checkAces() != -1)
	{
		switch (playerHand.getHandValue())
		{
            case 2:		return 'h';
            case 3:		return 'h';
            case 4:		return 'h';
            case 5:		return 'h';
            case 6:		return 'h';
            case 7:		return 'h';
            case 8:		return 'h';
            case 9:		return 'h';
            case 10:	return 'h';
            case 11:	return 'h';
            case 12:	return 'h';
            case 13:	return 'h';
            case 14:	return 'h';
            case 15:	return 'h';
            case 16:	return 'h';
            case 17:	return 'h';
            case 18:	switch (dealerHand.getDealerTopCard().getCardValue())
                        {
                            case 9:		return 'h';
                            case 10:	return 'h';
                            case 11:	return 'h';
                            default:    return 's';
                        }
            default:	return 's';
		}
	}
	
    // Now handle the hard totals
	else
	{
		switch (playerHand.getHandValue())
		{
            case 2:		return 'h';
            case 3:		return 'h';
            case 4:		return 'h';
            case 5:		return 'h';
            case 6:		return 'h';
            case 7:		return 'h';
            case 8:		return 'h';
            case 9:		return 'h';
            case 10:	return 'h';
            case 11:	return 'h';
            case 12:	switch (dealerHand.getDealerTopCard().getCardValue())
                        {
                            case 4:		return 's';
                            case 5:		return 's';
                            case 6:		return 's';
                            default:    return 'h';
                        }
            case 13:	switch (dealerHand.getDealerTopCard().getCardValue())
                        {
                            case 2:		return 's';
                            case 3:		return 's';
                            case 4:		return 's';
                            case 5:		return 's';
                            case 6:		return 's';
                            default:    return 'h';
                        }
            case 14:	switch (dealerHand.getDealerTopCard().getCardValue())
                        {
                            case 2:		return 's';
                            case 3:		return 's';
                            case 4:		return 's';
                            case 5:		return 's';
                            case 6:		return 's';
                            default:    return 'h';
                        }
            case 15:	switch (dealerHand.getDealerTopCard().getCardValue())
                        {
                            case 2:		return 's';
                            case 3:		return 's';
                            case 4:		return 's';
                            case 5:		return 's';
                            case 6:		return 's';
                            default:    return 'h';
                        }
            case 16:	switch (dealerHand.getDealerTopCard().getCardValue())
                        {
                            case 2:		return 's';
                            case 3:		return 's';
                            case 4:		return 's';
                            case 5:		return 's';
                            case 6:		return 's';
                            default:    return 'h';
                        }
            default:	return 's';
		}
	}

	return '!'; // Error: Fall back return
}
