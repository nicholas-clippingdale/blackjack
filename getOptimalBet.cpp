#include <cassert>

#include "Deck.h"
#include "Game.h"

double getOptimalBet(Deck &deck, double minBet, double bankroll)
{
    assert(deck.getNumDecks() > 0 &&
           "getOptimalBet() requires at least one deck in play");
    assert(minBet >= 0.0 &&
           "getOptimalBet() requires a non-negative minimum bet");
    assert(bankroll > 0.0 &&
           "getOptimalBet() requires a positive bankroll");
    
    if (deck.getTrueCount() < 0)
        return minBet;
    
    switch (deck.getTrueCount())
    {
        case 0:     return minBet;
        case 1:     return minBet;
        case 2:     return 0.0038 * bankroll;
        case 3:     return 0.0076 * bankroll;
        case 4:     return 0.0114 * bankroll;
        case 5:     return 0.0152 * bankroll;
        case 6:     return 0.0190 * bankroll;
        default:    return 0.0228 * bankroll;
    }
}
