#include <cassert>

#include "Hand.h"

#include "Strategy.h"

bool checkSurrender(Hand &playerHand, Hand &dealerHand, bool dealerHitsSoft17)
{
	assert(playerHand.getNumCards() == 2 &&
		"checkSurrender() requires two cards in the player's hand");
	assert((dealerHand.getNumCards() == 1 || dealerHand.getNumCards() == 2) &&
		"checkSurrender() requires one or two cards in the dealer's hand");

	// Retrieve some values from the hands to reduce duplication of function calls
    int aceIndex{ playerHand.checkAces() };
    int playerHandValue{ playerHand.getHandValue() };
    int dealerTopCardValue{ dealerHand.getDealerTopCard().getCardValue() };
    bool playerHasSix
    { playerHand[0].getCardValue() == 6 || playerHand[1].getCardValue() == 6 };
    bool playerHasSeven
    { playerHand[0].getCardValue() == 7 || playerHand[1].getCardValue() == 7 };
    bool playerHasNine
        { playerHand[0].getCardValue() == 9 || playerHand[1].getCardValue() == 9 };
    bool playerHasTen
    { playerHand[0].getCardValue() == 10 || playerHand[1].getCardValue() == 10 };
	
	if (dealerHitsSoft17 == false)
	{
        // Surrender on player hard fifteen and dealer shows a ten
		if (aceIndex == -1 && dealerTopCardValue == 10 && playerHandValue == 15)
			return true;
        else if (dealerTopCardValue == 9 || dealerTopCardValue == 10 ||
                  dealerTopCardValue == 11)
        {
            // Surrender on player 9,7 and dealer shows nine, ten, or ace
            if (playerHasNine == 1 && playerHasSeven == 1)
                return true;
            // Surrender on player 10,6 and dealer shows nine, ten, or ace
            if (playerHasSix == 1 && playerHasTen == 1)
                return true;
        }
	}
	else // The dealer hits soft seventeens
	{
		// Surrender on player hard fifteen and dealer shows an ace or ten
		if (aceIndex == -1 && playerHandValue == 15 &&
			(dealerTopCardValue == 10 || dealerTopCardValue == 11))
			return true;
		// Surrender on player hard seventeen and dealer shows an ace
		else if (aceIndex == -1 && dealerTopCardValue == 11 && playerHandValue == 17)
			return true;
		// Surrender on player 8,8 and dealer shows an ace
		else if (dealerTopCardValue == 11 &&
                 playerHand[0].getCardValue() == 8 && playerHand[1].getCardValue() == 8)
			return true;
        else if (dealerTopCardValue == 9 || dealerTopCardValue == 10 ||
                 dealerTopCardValue == 11)
        {
            // Surrender on player 9,7 and dealer shows nine, ten, or ace
            if (playerHasNine == 1 && playerHasSeven == 1)
                return true;
            // Surrender on player 10,6 and dealer shows nine, ten, or ace
            if (playerHasSix == 1 && playerHasTen == 1)
                return true;
        }
	}

	return false; // No surrender otherwise
}
