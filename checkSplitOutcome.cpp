#include <vector>
#include <cassert>

#include "Deck.h"
#include "Hand.h"

#include "playBlackjack.h"

double checkSplitOutcome(std::vector<Hand> split, Deck &deck, Hand &dealerHand, bool dealerHitSoft17)
{
	assert(split.size() >= 1 &&
		"The split vector must be at least of length two for checkSplitOutcome()");
	assert(deck.getNumDecks() > 0 &&
           "checkSplitOutcome() requires at least one deck in play");
	assert((dealerHand.getNumCards() == 1 || dealerHand.getNumCards() == 2) &&
		"checkSplitOutcome() requires the dealer's hand to have one or two cards");
    
    // Check how many hands busted
	int numHands{ static_cast<int>(split.size()) };
    int numDouble{ 0 };
    int numBustDouble{ 0 };
    int numBustNoDouble{ 0 };
    int handsWonNoDouble{ 0 };
    int handsWonDouble{ 0 };
    int handsLostNoDouble{ 0 };
    int handsLostDouble{ 0 };
    
    // Check how many hands busted
    for (const auto &hand : split)
    {
        if (hand.getHandValue() > 21)
        {
            if (hand.getDoubleDown() == true)
                ++numBustDouble;
            else
                ++numBustNoDouble;
        }
        else if (hand.getDoubleDown())
            ++numDouble;
    }
    
    // Check if all the hands busted
    if (numHands == (numBustNoDouble + numBustDouble))
        return static_cast<double>(-numBustNoDouble - 2 * numBustDouble); // All busted
    
    // Dealer plays their hand
    dealerHand = dealerPlay(deck, dealerHand, dealerHitSoft17);
    int dealerTotal{ dealerHand.getHandValue() };
    // Check if the dealer got a blackjack
    if (dealerTotal == 21 && dealerHand.getNumCards() == 2)
        return static_cast<double>(-numHands - numDouble); // Dealer got a blackjack
    // Check if the dealer busted
    if (dealerTotal > 21)
        return static_cast<double>(numHands + 2 * numDouble -
                                   numBustNoDouble - 2 * numBustDouble); // Dealer busted
    
    // Check the outcome of the remaining hands
    // Note the absence of a tie outcome below - it is unnecessary
    for (const auto &hand : split)
    {
        int playerTotal{ hand.getHandValue() };
        if (playerTotal <= 21)
        {
            if (playerTotal > dealerTotal)
            {
                if (hand.getDoubleDown() == true)
                    ++handsWonDouble;
                else
                    ++handsWonNoDouble;
            }
            else if (playerTotal < dealerTotal)
            {
                if (hand.getDoubleDown() == true)
                    ++handsLostDouble;
                else
                    ++handsLostNoDouble;
            }
        }
    }

	// Return the bet multiplier
	return static_cast<double>(handsWonNoDouble + 2 * handsWonDouble -
                               handsLostNoDouble - 2 * handsLostDouble
                               -numBustNoDouble - 2 * numBustDouble);
}
