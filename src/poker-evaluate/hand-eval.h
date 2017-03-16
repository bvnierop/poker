#ifndef _HAND_EVAL_H_
#define _HAND_EVAL_H_

#include <cstdint>
#include <string>

#include "bits.h"

namespace poker 
{
    ///////////////////////////////////////////////////////////////////////////
    // Utilities. TODO: move!
    ///////////////////////////////////////////////////////////////////////////
    template<typename E> constexpr auto to_integral(E e) -> typename std::underlying_type<E>::type 
    {
        return static_cast<typename std::underlying_type<E>::type>(e);
    }
    
    template<typename E, typename I = std::underlying_type_t<E>> constexpr E to_enum(I i) 
    {
        return static_cast<E>(i);
    }

    ///////////////////////////////////////////////////////////////////////////
    // Types
    ///////////////////////////////////////////////////////////////////////////
    typedef uint64_t BitHand;
    typedef uint64_t BitValue;
    typedef uint64_t BitCard;

    enum class Rank: uint64_t
    {
        HighCard = 0x0,
        OnePair = 0x1,
        TwoPair = 0x2,
        ThreeOfAKind = 0x3,
        Straight = 0x4,
        Flush = 0x5,
        FullHouse = 0x6,
        FourOfAKind = 0x7,
        StraightFlush = 0x8,
    };

    enum class Suit: uint64_t
    {
        Hearts = 0x0,
        Clubs = 0x1,
        Diamonds = 0x2,
        Spades = 0x3
    };

    enum class FaceValue: uint64_t
    {
        Two = 0x1, 
        Three = 0x2,
        Four = 0x3,
        Five = 0x4,
        Six = 0x5,
        Seven = 0x6,
        Eight = 0x7,
        Nine = 0x8,
        Ten = 0x9,
        Jack = 0xA,
        Queen = 0xB,
        King = 0xC,
        Ace = 0xD,
    };

    ///////////////////////////////////////////////////////////////////////////
    // Constants
    ///////////////////////////////////////////////////////////////////////////
    static constexpr uint64_t RankOffset = 13+13+4;
    static constexpr uint64_t MajorCardOffset = 13;
    static constexpr uint64_t SuitOffset = 26;
    static constexpr uint64_t RankFaceValuesMask = 0b1111111111111;

    ///////////////////////////////////////////////////////////////////////////
    // Function declarations
    ///////////////////////////////////////////////////////////////////////////

    BitValue evaluate_hand(BitHand hand);

    Rank rank(BitValue value);
    FaceValue major_card(BitValue value, int index = 0);
    uint64_t major_card_count(BitValue value);
    FaceValue minor_card(BitValue value, int index = 0);
    uint64_t minor_card_count(BitValue value);
    Suit value_suit(BitValue value);

    ///////////////////////////////////////////////////////////////////////////
    // Inline functions
    ///////////////////////////////////////////////////////////////////////////
    inline __fastcall FaceValue card_value(BitCard card)
    {
        // Index of most significant bit, divided by 4.
        return to_enum<FaceValue>(msb_index(card) >> 2);
    }

    inline __fastcall Suit card_suit(BitCard card)
    {
        // Index of most significant bit, modulo 3
        return to_enum<Suit>(msb_index(card) & 0x3);
    }

    /* inline __fastcall uint64_t _card_count(BitValue value) */
    /* { */
    /*     uint64_t cards = value & RankFaceValuesMask; */
    /*     uint64_t count = 0; */
    /*     while (cards) { */
    /*         cards &= ~(1ull << msb_index(cards)); */
    /*         ++count; */
    /*     } */
    /*     return count; */
    /* } */

    inline __fastcall FaceValue _card(BitValue value, int index)
    {
        uint64_t cards = value & RankFaceValuesMask;
        uint64_t current_card = 0;
        do {
            current_card = (1ull << msb_index(cards));
            cards &= ~current_card;
        } while (index--);
        return to_enum<FaceValue>(msb_index(current_card) + 1);
    }
}

#endif

