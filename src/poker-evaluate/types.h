#ifndef _TYPES_H_    
#define _TYPES_H_

#include <cstdint>
#include <type_traits>

namespace poker {

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

    template<typename E> constexpr auto to_integral(E e) -> typename std::underlying_type<E>::type 
    {
        return static_cast<typename std::underlying_type<E>::type>(e);
    }
    
    template<typename E, typename I = std::underlying_type_t<E>> constexpr E to_enum(I i) 
    {
        return static_cast<E>(i);
    }

    static constexpr uint64_t RankOffset = 13+13+4;
    static constexpr uint64_t MajorCardOffset = 13;
    static constexpr uint64_t SuitOffset = 26;
    static constexpr uint64_t RankFaceValuesMask = 0b1111111111111;

}

#endif // _TYPES_H_
