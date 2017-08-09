#include <cassert>

#include "Deck.h"
#include "Hand.h"

#include "playBlackjack.h"

double regularPlay(Deck &deck, Hand &playerHand, Hand &dealerHand, bool dealerHitSoft17)
{
    assert(deck.getNumDecks() > 0 &&
           "regularPlay() requires at least one deck in play");
    assert(playerHand.getNumCards() >= 2 &&
           "regularPlay() requires at least two cards in the player's hand");
    assert(dealerHand.getNumCards() == 2 &&
           "doPeek() requires two cards in the dealer's hand");
    
    int playerTotal{ playerHand.getHandValue() }, dealerTotal{ dealerHand.getHandValue() };
    bool tookDoubleDown{ playerHand.getDoubleDown() };
    bool tookInsurance{ dealerHand.getInsurance() };
    
    // The player plays their hand if a double down was not taken
    if (tookDoubleDown == false)
    {
        playerHand = playHand(deck, playerHand, dealerHand);
        playerTotal = playerHand.getHandValue();
        // Check if the player busted
        if (playerTotal > 21)
        {
            // Check if the player lost an insurance bet
            if (tookInsurance == true)
                return -1.5; // Return loss and lost insurance bet
            else
                return -1.0; // Player busted - return loss
        }
    }
    
    // Dealer plays their hand
    dealerHand = dealerPlay(deck, dealerHand, dealerHitSoft17);
    dealerTotal = dealerHand.getHandValue();
    
    // Check if the dealer busted
    if (dealerTotal > 21)
    {
        // Check if the player lost an insurance bet
        if (tookInsurance == true)
        {
            // Check if the player doubled down
            if (tookDoubleDown == true)
                return 1.5; // Return double down win but insurance loss
            else
                return 0.5; // Return win but insurance loss
        }
        else // Insurance was not taken
        {
            // Check if the player doubled down
            if (tookDoubleDown == true)
                return 2.0; // Return double down win
            else
                return 1.0; // Return win
        }
    }
    
    // Neither the player nor dealer busted
    if (tookInsurance == true)
    {
        if (tookDoubleDown == true)
        {
            if (playerTotal > dealerTotal)
                return 1.5; // Return double down win but insurance loss
            else if (playerTotal < dealerTotal)
                return -2.5; // Return double down loss and insurance loss
            else
                return -0.5; // Return tie and insurance loss
        }
        else // Double down was not taken
        {
            if (playerTotal > dealerTotal)
                return 0.5; // Return win but insurance loss
            else if (playerTotal < dealerTotal)
                return -1.5; // Return loss and insurance loss
            else
                return -0.5; // Return tie and insurance loss
        }
    }
    else // Insurance was not taken
    {
        if (tookDoubleDown == true)
        {
            if (playerTotal > dealerTotal)
                return 2.0; // Return double down win
            else if (playerTotal < dealerTotal)
                return -2.0; // Return double down loss
            else
                return 0.0; // Return tie
        }
        if (playerTotal > dealerTotal)
            return 1.0; // Return win
        else if (playerTotal < dealerTotal)
            return -1.0; // Return loss
        else
            return 0.0; // Return tie
    }
}
