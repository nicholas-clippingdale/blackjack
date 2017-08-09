#include <cassert>

#include "Hand.h"

#include "Strategy.h"

bool checkSplit(Hand &playerHand, Hand &dealerHand)
{
	assert(playerHand.getNumCards() == 2 &&
		"checkSplit() requires two cards in the player's hand");
	assert(dealerHand.getNumCards() >= 1 &&
		"checkSplit() requires at least one card in the dealer's hand");
	assert(playerHand[1].getCardValue() == playerHand[0].getCardValue() &&
		"checkSplit() requires the two cards in the hand to be of the same value");

	switch (playerHand[0].getCardValue())
	{
        case 2:		switch (dealerHand.getDealerTopCard().getCardValue())
                    {
                        case 8:		return false;
                        case 9:		return false;
                        case 10:	return false;
                        case 11:	return false;
                        default:	return true;
                    }
        case 3:		switch (dealerHand.getDealerTopCard().getCardValue())
                    {
                        case 8:		return false;
                        case 9:		return false;
                        case 10:	return false;
                        case 11:	return false;
                        default:	return true;
                    }
        case 4:		switch (dealerHand.getDealerTopCard().getCardValue())
                    {
                        case 5:		return true;
                        case 6:		return true;
                        default:	return false;
                    }
        case 5:		return false;
        case 6:		switch (dealerHand.getDealerTopCard().getCardValue())
                    {
                        case 7:		return false;
                        case 8:		return false;
                        case 9:		return false;
                        case 10:	return false;
                        case 11:	return false;
                        default:	return true;
                    }
        case 7:		switch (dealerHand.getDealerTopCard().getCardValue())
                    {
                        case 8:		return false;
                        case 9:		return false;
                        case 10:	return false;
                        case 11:	return false;
                        default:	return true;
                    }
        case 8:		return true;
        case 9:		switch (dealerHand.getDealerTopCard().getCardValue())
                    {
                        case 7:		return false;
                        case 10:	return false;
                        case 11:	return false;
                        default:	return true;
                    }
        case 10:	return false;
        default:	return true;
	}
}
