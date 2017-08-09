/**
    Strategy.h contains all the functions concerning strategic choices the player
        must make
 
    Nicholas Clippingdale
    Version 1.0
    28th July 2017
 */

#pragma once

#include "Deck.h"
#include "Hand.h"

bool checkInsurance(Deck &deck);
bool checkDoubleDown(Hand &playerHand, Hand &dealerHand);
bool checkSurrender(Hand &playerHand, Hand &dealerHand, bool dealerHitsSoft17);
bool checkSplit(Hand &playerHand, Hand &dealerHand);
char getStrategyChoice(Deck &deck, Hand &playerHand, Hand &dealerHand);
char getPlayerChoice();
