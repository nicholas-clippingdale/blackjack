#include <iostream>
#include <cassert>
#include <ctime>
#include <cstdlib>

#include "Deck.h"
#include "Hand.h"
#include "Game.h"

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	rand();

	double deckPenetration{ 0.8 };		// How far through the decks before a shuffle
										// Note: 0.0 < deckPenetration <= 1.0
										// Note: Having a high deck penetration can lead to
										//       ending the deck in the middle of a hand.
										//       This will lead to an error.
	int numDecks{ 6 }; // The number of decks in play
	int buryCards{ 0 }; // How many cards get burned before hands are dealt?
						// Note: burnCards < numDecks * 52

	assert(deckPenetration > 0.0 && deckPenetration <= 1.0 &&
		"deckPenetration needs to be 0.0 < deckPenetration <= 1.0");
	assert(buryCards < (52 * numDecks) &&
		"burnCards needs to be less than the size of the deck");
    
    Deck deck(numDecks);
    deck.shuffleDeck();
    
    double bankroll{ 3000.0 };
    double minBet{ 5.0 };
    double currentFunds{ bankroll };
    long numHands{ 0 };
    
    for (int i = 0; i < 2000; ++i)
    {
        if (static_cast<double>(deck.getIndex()) >
            deckPenetration * 52.0 * static_cast<double>(deck.getNumDecks()))
        {
            deck = Deck(numDecks);
            deck.shuffleDeck();
        }
        
        double bet{ getOptimalBet(deck, minBet, bankroll) };
        double result{ playBlackjack(deck) };
        
        currentFunds += bet * result;
        ++numHands;
    }
    
    std::cout << numHands << '\t' << currentFunds << '\n';
	
	return 0;
}
