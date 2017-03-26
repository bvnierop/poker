#include "../third-party/catch.hpp"
#include "catch-rspec.hpp"
#include "../poker-evaluate/hand-eval.h"
#include "../poker-evaluate/hand-parse.h"
#include "../poker-evaluate/hand-value.h"
#include "../poker-evaluate/hand-iterate.h"
#include "../poker-evaluate/bits.h"

#include <set>
#include <map>
#include <iostream>

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

    It("detects one pair, when it's a pair of aces") {
        ExpectHand("Ah Ac 5d Qs Kc 2h 7c", Rank::OnePair,
                FaceValue::Ace,
                { FaceValue::King, FaceValue::Queen, FaceValue::Seven });
    }

    It("detects a flush") {
        ExpectHand("Ah Kh 9h 8h 5h 3s 2s", Rank::Flush,
            FaceValue::Ace,
            { FaceValue::King, FaceValue::Nine, FaceValue::Eight, FaceValue::Five });
    }

    It("detects a spade flush") {
        ExpectHand("As Ks 9s 8s 5s 3h 2h", Rank::Flush,
            FaceValue::Ace,
            { FaceValue::King, FaceValue::Nine, FaceValue::Eight, FaceValue::Five });
    }

    It("detects a flush over a three of a kind") {
        ExpectHand("As Ks 9s 8s 5s Ah Ad", Rank::Flush,
            FaceValue::Ace,
            { FaceValue::King, FaceValue::Nine, FaceValue::Eight, FaceValue::Five });
    }

    It("detects a straight") {
        ExpectHand("Kh Qc Jd Ts 9h 7c 2d", Rank::Straight,
                FaceValue::King, {});
    }

    It("detects the highest straight") {
        ExpectHand("Ah Kc Qd Js Th 9c 2d", Rank::Straight,
                FaceValue::Ace, {});
    }

    It("detects an ace low straight") {
        ExpectHand("Ah 2c 3d 4s 5h 9c Td", Rank::Straight,
                FaceValue::Five, {});
    }

    It("detects a straight over a three of a kind") {
        ExpectHand("Ah 2c 3d 4s 5h Ac Ad", Rank::Straight,
                FaceValue::Five, {});
    }

    It("detects a straight flush") {
        ExpectHand("Kh Qh Jh Th 9h 7c 2d", Rank::StraightFlush,
                FaceValue::King, {});
    }

    It("detects an ace low straight flush") {
        ExpectHand("5h 4h 3h 2h Ah 7c 2d", Rank::StraightFlush,
                FaceValue::Five, {});
    }

    It("recognizes a high card") {
        ExpectHand("Ah Qc Td 8s 6h 4c 2d", Rank::HighCard,
                FaceValue::Ace,
                { FaceValue::Queen, FaceValue::Ten, FaceValue::Eight, FaceValue::Six });
    }

    It("maps to the correct number of unique values") {
        // Source: http://suffe.cool/poker/evaluator.html
        static std::map<Rank, int> expected_counts = {
            { Rank::StraightFlush, 40 },
            { Rank::FourOfAKind, 624},
            { Rank::FullHouse, 3744 },
            { Rank::Flush, 5108 },
            { Rank::Straight, 10200 },
            { Rank::ThreeOfAKind, 54912 },
            { Rank::TwoPair, 123552 },
            { Rank::OnePair, 1098240 },
            { Rank::HighCard, 1302540 }
        };

        static std::map<Rank, size_t> expected_distinct_counts = {
            { Rank::StraightFlush, 10 },
            { Rank::FourOfAKind, 156},
            { Rank::FullHouse, 156 },
            { Rank::Flush, 1277 },
            { Rank::Straight, 10 },
            { Rank::ThreeOfAKind, 858 },
            { Rank::TwoPair, 858 },
            { Rank::OnePair, 2860 },
            { Rank::HighCard, 1277 }
        };

        std::map<Rank, int> rank_counts;
        std::map<Rank, std::set<BitValue>> distinct_rank_counts;

        iterate_hands(5, [&](BitHand hand) 
        {
            BitValue value = evaluate_hand(hand);
            rank_counts[rank(value)]++;
            distinct_rank_counts[rank(value)].insert(value);
        });

        /* std::cout << "Straight flush:  " << rank_counts[Rank::StraightFlush] << std::endl; */
        /* std::cout << "Four of a kind:  " << rank_counts[Rank::FourOfAKind] << std::endl; */
        /* std::cout << "Full House:      " << rank_counts[Rank::FullHouse] << std::endl; */
        /* std::cout << "Flush:           " << rank_counts[Rank::Flush] << std::endl; */
        /* std::cout << "Straight:        " << rank_counts[Rank::Straight] << std::endl; */
        /* std::cout << "Three of a kind: " << rank_counts[Rank::ThreeOfAKind] << std::endl; */
        /* std::cout << "Two Pair:        " << rank_counts[Rank::TwoPair] << std::endl; */
        /* std::cout << "One Pair:        " << rank_counts[Rank::OnePair] << std::endl; */
        /* std::cout << "HighCard:        " << rank_counts[Rank::HighCard] << std::endl; */

        /* std::cout << "Straight flush:  " << distinct_rank_counts[Rank::StraightFlush].size() << std::endl; */
        /* std::cout << "Four of a kind:  " << distinct_rank_counts[Rank::FourOfAKind].size() << std::endl; */
        /* std::cout << "Full House:      " << distinct_rank_counts[Rank::FullHouse].size() << std::endl; */
        /* std::cout << "Flush:           " << distinct_rank_counts[Rank::Flush].size() << std::endl; */
        /* std::cout << "Straight:        " << distinct_rank_counts[Rank::Straight].size() << std::endl; */
        /* std::cout << "Three of a kind: " << distinct_rank_counts[Rank::ThreeOfAKind].size() << std::endl; */
        /* std::cout << "Two Pair:        " << distinct_rank_counts[Rank::TwoPair].size() << std::endl; */
        /* std::cout << "One Pair:        " << distinct_rank_counts[Rank::OnePair].size() << std::endl; */
        /* std::cout << "HighCard:        " << distinct_rank_counts[Rank::HighCard].size() << std::endl; */

        Expect(expected_counts.size() == 9);
        for (auto pair : rank_counts) {
            Expect(pair.first <= Rank::StraightFlush);
            Expect(pair.second == expected_counts[pair.first]);
        }

        for (auto pair : distinct_rank_counts) {
            Expect(pair.first <= Rank::StraightFlush);
            Expect(pair.second.size() == expected_distinct_counts[pair.first]);
        }
    }
}

