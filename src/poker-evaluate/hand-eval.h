#ifndef _HAND_EVAL_H_
#define _HAND_EVAL_H_

#include <cstdint>
#include <string>

namespace poker 
{
    ///////////////////////////////////////////////////////////////////////////
    // Utilities. TODO: move!
    ///////////////////////////////////////////////////////////////////////////
    inline uint64_t __fastcall bsr(const uint64_t &number)
    {
        uint64_t position = 0;
        asm("bsrq %1, %0" : "=r" (position) : "r" (number));
        return position;
    }

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
        None,
        Pair
    };

    enum class Face: uint64_t
    {
        Hearts = 0x0,
        Clubs = 0x1,
        Diamonds = 0x2,
        Spades = 0x3
    };

    enum class Value: uint64_t
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
    // Function declarations
    ///////////////////////////////////////////////////////////////////////////
    bool is_value_char(const char& c);
    bool is_face_char(const char &c);


    BitHand parse_hand(const std::string &description);
    BitCard parse_card(const std::string &description);

    BitValue evaluate_hand(BitHand hand);
    Rank rank(BitValue value);

    ///////////////////////////////////////////////////////////////////////////
    // Inline functions
    ///////////////////////////////////////////////////////////////////////////
    inline __fastcall Value card_value(BitCard card)
    {
        // Index of most significant bit, divided by 4.
        return to_enum<Value>(bsr(card) >> 2);
    }

    inline __fastcall Face card_face(BitCard card)
    {
        // Index of most significant bit, modulo 3
        return to_enum<Face>(bsr(card) & 0x3);
    }
}

#endif
