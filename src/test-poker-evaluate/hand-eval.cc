#include "../third-party/catch.hpp"
#include "catch-rspec.hpp"
#include "../poker-evaluate/hand-eval.h"
#include "../poker-evaluate/hand-parse.h"

using namespace poker;

Describe("hand eval") {
    It("detects a four of a kind") {
        BitHand hand = parse_hand("Kh Kc Kd Ks Ac 2h 7c");
        BitValue value = evaluate_hand(hand);
        Expect(rank(value) == Rank::FourOfAKind);
        Expect(major_card(value) == FaceValue::King);
        Expect(minor_card(value) == FaceValue::Ace);
    }

    It("detects a three of a kind") {
        BitHand hand = parse_hand("Kh Kc Kd Qs Ac 2h 7c");
        BitValue value = evaluate_hand(hand);
        Expect(rank(value) == Rank::ThreeOfAKind);
        Expect(major_card(value) == FaceValue::King);
        Expect(minor_card(value) == FaceValue::Ace);
        Expect(minor_card(value, 1) == FaceValue::Queen);
    }
}



// TODO: Move rank disection to its own file
Describe("parsing a hand value") {
    /*
        A hand value is represented by bits. The thirteen lowest bits
        represent minor cards. These are usually kickers. The only exception
        to this rule is the Full House, where the bit set in the low thirteen
        bits represents the card of which there are two. 

        The next thirteen bits represent the main value of the hand:
            - High Card         The highest card value
            - One Pair          The paired card value
            - Two Pair          Both paired cards values
            - Three of a Kind   The tripled card value
            - Straight          The highest card value
            - Flush             The highest card value
            - Full House        The tripled card value
            - Four of a Kind    The quadrupled card value
            - Straight Flush    The highest card value

        The next four bits represent the suit, if applicable. This applies only
        to flushes and straight flushes.

        Finally, the next nine bits represent the hand rank, the lowest rank 
        being High Card, and the highest one being Straight Flush. A Royal 
        Flush is just an ace high Straight Flush.
    */


    It("Contains the rank") {
        BitValue highCardFaceValue = 0b1000000000000000000000000000000ull;
        Expect(rank(highCardFaceValue) == Rank::HighCard);
        
        BitValue straightFlushFaceValue = 0b100000000000000000000000000000000000000ull;
        Expect(rank(straightFlushFaceValue) == Rank::StraightFlush);
    }

    It("Contains the major cards") {
        BitValue twoPairAD = 0b100000010000000000010000000000000ull;
        Expect(major_card_count(twoPairAD) == 2);
        Expect(major_card(twoPairAD) == FaceValue::Ace);
        Expect(major_card(twoPairAD, 1) == FaceValue::Two);
    }

    It("Does not contain cards out of range") {
        BitValue value = 0; // no cards
        Expect(major_card_count(value) == 0);
    }

    It("Contains the minor cards") {
        BitValue onePair = 0b10000000000000000011110000000000ull;
        Expect(minor_card_count(onePair) == 3);
        Expect(minor_card(onePair) == FaceValue::Ace);
        Expect(minor_card(onePair, 1) == FaceValue::King);
        Expect(minor_card(onePair, 2) == FaceValue::Queen);
    }

    It("Contains the suit when applicable") {
        BitHand flush = 0b100000100011110100000000000000000000ull;
        Expect(value_suit(flush) == Suit::Spades);
    }
}

