#include <cassert>

#include "Deck.h"

#include "Strategy.h"

bool checkInsurance(Deck &deck)
{
	assert(deck.getNumDecks() > 0 &&
           "checkInsurance() requires at least one deck in play");

     // Always insure when the true count is at least three
	if (deck.getTrueCount() >= 3)
		return true;
	else
		return false;
}
