#include <cassert>

#include "Hand.h"

#include "Strategy.h"

bool checkDoubleDown(Hand &playerHand, Hand &dealerHand)
{
    assert(playerHand.getNumCards() == 2 &&
           "checkDoubleDown() requires the player have two cards");
    assert((dealerHand.getNumCards() == 1 || dealerHand.getNumCards() == 2) &&
           "checkDoubleDown() requires the dealer have one or two cards");

	// Check for soft totals
	if (playerHand.checkAces() != -1)
	{
		switch (playerHand.getHandValue())
		{
		case 13:	switch (dealerHand.getDealerTopCard().getCardValue())
					{
					case 5:		return true;
					case 6:		return true;
					default:	return false;
					}
		case 14:	switch (dealerHand.getDealerTopCard().getCardValue())
					{
					case 5:		return true;
					case 6:		return true;
					default:	return false;
					}
		case 15:	switch (dealerHand.getDealerTopCard().getCardValue())
					{
					case 4:		return true;
					case 5:		return true;
					case 6:		return true;
					default:	return false;
					}
		case 16:	switch (dealerHand.getDealerTopCard().getCardValue())
					{
					case 4:		return true;
					case 5:		return true;
					case 6:		return true;
					default:	return false;
					}
		case 17:	switch (dealerHand.getDealerTopCard().getCardValue())
					{
					case 3:		return true;
					case 4:		return true;
					case 5:		return true;
					case 6:		return true;
					default:	return false;
					}
		case 18:	switch (dealerHand.getDealerTopCard().getCardValue())
					{
					case 3:		return true;
					case 4:		return true;
					case 5:		return true;
					case 6:		return true;
					default:	return false;
					}
		default:	return false;
		}
	}
    
	// Check for hard totals
	else
	{
		switch (playerHand.getHandValue())
		{
		case 9:		switch (dealerHand.getDealerTopCard().getCardValue())
					{
					case 3:		return true;
					case 4:		return true;
					case 5:		return true;
					case 6:		return true;
					default:	return false;
					}
		case 10:	switch (dealerHand.getDealerTopCard().getCardValue())
					{
					case 10:	return false;
					case 11:	return false;
					default:	return true;
					}
		case 11:	switch (dealerHand.getDealerTopCard().getCardValue())
					{
					case 11:	return false;
					default:	return true;
					}
		default:	return false;
		}
	}
}
