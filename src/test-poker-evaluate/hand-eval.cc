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

// So I really have to test parsing a hand, first...
Describe("parse hand") {
    It("parses one card") {
        BitCard card = parse_card("4s");
        Expect(card == 0b1000000000000000);
        Expect(card_value(card) == Value::Four);
        Expect(card_face(card) == Face::Spades);
    }

    It("parses another card") {
        BitCard card = parse_card("Th");
        Expect(card == 0b0001000000000000000000000000000000000000ull);
        Expect(card_value(card) == Value::Ten);
        Expect(card_face(card) == Face::Hearts);
    }
}
