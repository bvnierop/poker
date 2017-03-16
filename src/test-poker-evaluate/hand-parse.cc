#include "../third-party/catch.hpp"
#include "catch-rspec.hpp"
#include "../poker-evaluate/hand-parse.h"

using namespace poker;

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

