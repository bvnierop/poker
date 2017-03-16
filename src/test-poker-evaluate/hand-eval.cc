#include "../third-party/catch.hpp"
#include "catch-rspec.hpp"
#include "../poker-evaluate/hand-eval.h"
#include "../poker-evaluate/hand-parse.h"
#include "../poker-evaluate/hand-value.h"

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

