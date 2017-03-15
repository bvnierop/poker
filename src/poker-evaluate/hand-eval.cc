#include "hand-eval.h"

#include <vector>
#include <string>

#include <iostream>

namespace poker {
    void print_bits(uint64_t bits) {
        for (int i = 63; i >= 0; --i) {
            std::cout << ((bits & (1ull << i)) >> i);
            if (!(i%4)) std::cout << " ";
        }
        std::cout << std::endl;
    }

    inline __fastcall bool is_value_char(const char& c) 
    {
        static const std::string values("23456789TJQKAtjqka");
        return values.find(c) != values.npos;
    }
    
    inline __fastcall bool is_suit_char(const char &c)
    {
        static const std::string suits("hcdsHCDS");
        return suits.find(c) != suits.npos;
    }

    BitHand parse_hand(const std::string &description)
    {
        BitHand hand = 0;
        for (size_t i = 0; i < description.size(); ++i) {
            char a = description[i];
            char b = description[i+1];
            if (is_value_char(a) && is_suit_char(b))  {
                hand |= parse_card(description.substr(i, 2));
            }
        }

        return hand;
    }

    BitValue evaluate_hand(BitHand hand)
    {
        BitValue value = 0;

        uint64_t countidx = 0;
        for (uint64_t temp = hand; temp; temp &= (temp - 1)) {
            uint64_t offset = (bsl(temp) >> 2) << 2; // offset of the nibble
            uint64_t nibble = (countidx >> offset) & 0xFull; // zero out everything but the nibble
            nibble <<= 1; // increment the amount of cards in the nibble
            bool zero = nibble == 0;
            nibble = (nibble & ~0x1) | (-zero & 0x1); // if the nibble is zero, set it to 1, because incrementing zero doesn't
                                                      // doesn't do anything
            countidx &= (0xFFFFFFFFFFFFFFFFull ^ (0xFull << offset)); // set the nibble at the correct offset to all zeroes
            countidx |= nibble << offset; // place the nibble back
        }

        uint64_t quads = countidx & 0x8888888888888888ull;
        if (quads) {
            value |= (1ull << to_integral(Rank::FourOfAKind)) << RankOffset;
            value |= (1ull << ((bsr(quads) >> 2) - 1)) << MajorCardOffset;
            value |= 1ull << ((bsr(countidx & ~quads) >> 2) - 1);
        }

        uint64_t triplets = countidx & 0x4444444444444444ull;
        if (triplets) {
            value |= (1ull << to_integral(Rank::ThreeOfAKind)) << RankOffset; // duplication, use a function
            value |= (1ull << ((bsr(triplets) >> 2) - 1)) << MajorCardOffset;
            uint64_t kickers = countidx;
            for (int i = 0; i < 2; ++i) {
                value |= 1ull << ((bsr(kickers & ~triplets) >> 2) - 1);
                kickers &= ~(1ull << bsr(kickers));
            }
        }

        return value;
    }

    Rank rank(BitValue value)
    {
        return to_enum<Rank>(bsr(value >> RankOffset));
    }

    FaceValue major_card(BitValue value, int index)
    {
        return _card(value >> MajorCardOffset, index);
    }

    uint64_t major_card_count(BitValue value)
    {
        return _card_count(value >> MajorCardOffset);
    }

    FaceValue minor_card(BitValue value, int index)
    {
        return _card(value, index);
    }

    uint64_t minor_card_count(BitValue value)
    {
        return _card_count(value);
    }

    Suit value_suit(BitValue value)
    {
        return to_enum<Suit>(bsr((value >> SuitOffset) & 0xF));
    }

    BitCard parse_card(const std::string &description)
    {
        static constexpr uint64_t values[] = {
           0, /* 0 */ 0, /* 1 */
           to_integral(FaceValue::Two),
           to_integral(FaceValue::Three),
           to_integral(FaceValue::Four),
           to_integral(FaceValue::Five),
           to_integral(FaceValue::Six),
           to_integral(FaceValue::Seven),
           to_integral(FaceValue::Eight),
           to_integral(FaceValue::Nine),
           0, /* : */ 0, /* ; */ 0, /* < */ 0, /* = */ 0, /* > */ 0, /* ? */ 0, /* @ */
           to_integral(FaceValue::Ace),
           0, /* B */ 0, /* C */ 0, /* D */ 0, /* E */ 0, /* F */ 0, /* G */ 0, /* H */ 0, /* I */
           to_integral(FaceValue::Jack),
           to_integral(FaceValue::King),
           0, /* L */ 0, /* M */ 0, /* N */ 0, /* O */ 0, /* P */
           to_integral(FaceValue::Queen),
           0, /* R */ 0, /* S */
           to_integral(FaceValue::Ten),
           0, /* U */ 0, /* V */ 0, /* W */ 0, /* X */ 0, /* Y */ 0, /* Z */ 0, /* [ */ 0, /* \ */
           0, /* ] */ 0, /* ^ */ 0, /* _ */ 0, /* ` */
           to_integral(FaceValue::Ace),
           0, /* b */ 0, /* c */ 0, /* d */ 0, /* e */ 0, /* f */ 0, /* g */ 0, /* h */ 0, /* i */
           to_integral(FaceValue::Jack),
           to_integral(FaceValue::King),
           0, /* l */ 0, /* m */ 0, /* n */ 0, /* o */ 0, /* p */
           to_integral(FaceValue::Queen),
           0, /* r */ 0, /* s */
           to_integral(FaceValue::Ten),
        };

        static constexpr uint64_t suits[] = {
           0, /* A */ 0, /* B */ to_integral(Suit::Clubs), /* C */ to_integral(Suit::Diamonds), /* D */ 0, /* E */
           0, /* F */ 0, /* G */ to_integral(Suit::Hearts), /* H */ 0, /* I */ 0, /* J */
           0, /* K */ 0, /* L */ 0, /* M */ 0, /* N */ 0, /* O */
           0, /* P */ 0, /* Q */ 0, /* R */ to_integral(Suit::Spades), /* S */ 0, /* T */
           0, /* U */ 0, /* V */ 0, /* W */ 0, /* X */ 0, /* Y */
           0, /* Z */
           0, /* [ */ 0, /* \ */ 0, /* ] */ 0, /* ^ */ 0, /* _ */ 0, /* ` */
           0, /* a */ 0, /* b */ to_integral(Suit::Clubs), /* c */ to_integral(Suit::Diamonds), /* d */ 0, /* e */
           0, /* f */ 0, /* g */ to_integral(Suit::Hearts), /* h */ 0, /* i */ 0, /* j */
           0, /* k */ 0, /* l */ 0, /* m */ 0, /* n */ 0, /* o */
           0, /* p */ 0, /* q */ 0, /* r */ to_integral(Suit::Spades), /* s */ 0, /* t */
           0, /* u */ 0, /* v */ 0, /* w */ 0, /* x */ 0, /* y */ 0,
           /* z */
        };

        uint64_t suit = suits[(int)description[1] - 'A'];
        uint64_t value = values[(int)description[0] - '0'];
        bool is_ace = value == to_integral(FaceValue::Ace);
        uint64_t ace_mask = 1 << suit;

        uint64_t card = (1ull << suit) <<
            (value << 2);

        // Conditionally set ace_mask, when is_ace is true.
        return (card & ~ace_mask) | (-is_ace & ace_mask);
    }
}

