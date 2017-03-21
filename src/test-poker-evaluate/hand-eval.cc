#include "../third-party/catch.hpp"
#include "catch-rspec.hpp"
#include "../poker-evaluate/hand-eval.h"
#include "../poker-evaluate/hand-parse.h"
#include "../poker-evaluate/hand-value.h"

using namespace poker;

void ExpectHand(const std::string &handString,
        Rank expectedRank,
        FaceValue expectedMajor,
        const std::vector<FaceValue> &expectedMinors)
{
    BitHand hand = parse_hand(handString);
    BitValue value = evaluate_hand(hand);
    Expect(rank(value) == expectedRank);
    Expect(major_card(value) == expectedMajor);
    for (size_t i = 0; i < expectedMinors.size(); ++i) {
        Expect(minor_card(value, i) == expectedMinors[i]);
    }
}

void ExpectHand(const std::string &handString,
        Rank expectedRank,
        const std::vector<FaceValue> &expectedMajors,
        const std::vector<FaceValue> &expectedMinors)
{
    BitHand hand = parse_hand(handString);
    BitValue value = evaluate_hand(hand);
    Expect(rank(value) == expectedRank);
    for (size_t i = 0; i < expectedMajors.size(); ++i) {
        Expect(major_card(value, i) == expectedMajors[i]);
    }
    for (size_t i = 0; i < expectedMinors.size(); ++i) {
        Expect(minor_card(value, i) == expectedMinors[i]);
    }
}

Describe("hand eval") {
    It("detects a four of a kind") {
        ExpectHand("Kh Kc Kd Ks Ac 2h 7c", Rank::FourOfAKind,
                FaceValue::King,
                { FaceValue::Ace });
    }

    It("detects a three of a kind") {
        ExpectHand("Kh Kc Kd Qs Ac 2h 7c", Rank::ThreeOfAKind,
                FaceValue::King,
                { FaceValue::Ace, FaceValue::Queen });
    }

    It("detects a pair") {
        ExpectHand("Kh Kc 5d Qs Ac 2h 7c", Rank::OnePair,
                FaceValue::King,
                { FaceValue::Ace, FaceValue::Queen, FaceValue::Seven });
    }

    It("detects a three of a kind/pair full house") {
        ExpectHand("Kh Kc Kd As Ac 2h 7c", Rank::FullHouse,
                FaceValue::King, { FaceValue::Ace });
    }

    It("detects a double three of a kind full house") {
        ExpectHand("Kh Kc Kd Qs Qc Qh 7c", Rank::FullHouse,
                FaceValue::King, { FaceValue::Queen });
    }

    It("detects two pair") {
        ExpectHand("Kh Kc 2d Qs Qc 5h 7c", Rank::TwoPair,
                { FaceValue::King, FaceValue::Queen },
                { FaceValue::Seven });
    }
}

