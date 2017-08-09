/**
    playBlackjack.h contains all the functions requried to play blackjack
        and all the associated variations of play
 
    Nicholas Clippingdale
    Version 1.0
    28th July 2017
 */

#pragma once

#include <vector>

#include "Deck.h"
#include "Hand.h"

double doPeek(Deck &deck, Hand &playerHand, Hand &dealerHand, bool takeInsurance);
std::vector<Hand> doSplit(Deck &deck, Hand &playerHand, Hand &dealerHand, bool takeDoubleDown, bool resplitAces, bool doubleDownAfterSplit);
double checkSplitOutcome(std::vector<Hand> split, Deck &deck, Hand &dealerHand, bool dealerHitSoft17);
Hand& playHand(Deck &deck, Hand &playerHand, Hand &dealerHand);
Hand& dealerPlay(Deck &deck, Hand &dealerHand, bool dealerHitSoft17);
Hand& hitSoft17(Deck &deck, Hand &dealerHand);
double regularPlay(Deck &deck, Hand &playerHand, Hand &dealerHand, bool dealerHitSoft17);
