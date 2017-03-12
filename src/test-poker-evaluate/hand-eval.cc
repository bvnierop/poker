#include "../third-party/catch.hpp"
#include "catch-rspec.hpp"
#include "../poker-evaluate/hand-eval.h"

using namespace poker;

/* Describe("hand eval") { */
/*     Context("detect pair") { */
/*         It("recognizes a pair") { */
/*             BitHand hand = parse_hand("Ac Ah 2s 4h 6c 8d Ts"); */
/*             BitValue value = evaluate_hand(hand); */
/*             Expect(rank(value) == Rank::Pair); */
/*             // expect aces to be the paired card */
/*         } */

/*         It("recognizes kickers") { */
/*         } */
/*     } */
/* } */


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

// TODO: move parse tests and functions to their own files
Describe("parse hand") {
    /*
        A hand is represented by bits. Each card is represented by one bit.
        Each nibble represents a card value, and within each nibble, each bit
        represents a suit.

        The odd one out is the ace. In order to help recognize an ace low 
        straight, the ace has a bit lower than the deuce and a bit higher than
        the king.
    */

    It("parses one card") {
        BitCard card = parse_card("4s");
        Expect(card == 0x8000ull);
        Expect(card_value(card) == FaceValue::Four);
        Expect(card_suit(card) == Suit::Spades);
    }

    It("parses another card") {
        BitCard card = parse_card("Th");
        Expect(card == 0x1000000000ull);
        Expect(card_value(card) == FaceValue::Ten);
        Expect(card_suit(card) == Suit::Hearts);
    }

    It("has an extra bit for an ace") {
        BitCard card = parse_card("Ah");
        Expect(card == 0x10000000000001ull);

        card = parse_card("As");
        Expect(card == 0x80000000000008ull);
    }

    It("parses multiple cards") {
        BitHand hand = parse_hand("2c 2h");
        Expect(hand == 0b00110000);
    }
}
