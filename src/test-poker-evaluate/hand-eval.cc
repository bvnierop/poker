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

// TODO: move parse tests and functions to their own files
Describe("parse hand") {
    It("parses one card") {
        BitCard card = parse_card("4s");
        Expect(card == 0x8000ull);
        Expect(card_value(card) == Value::Four);
        Expect(card_face(card) == Face::Spades);
    }

    It("parses another card") {
        BitCard card = parse_card("Th");
        Expect(card == 0x1000000000ull);
        Expect(card_value(card) == Value::Ten);
        Expect(card_face(card) == Face::Hearts);
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
