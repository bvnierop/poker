#include "hand-eval.h"

#include <vector>
#include <string>

namespace poker {
    bool is_value_char(const char& c) 
    {
        static const std::string values("23456789TJQKAtjqka");
        return values.find(c) != values.npos;
    }
    
    bool is_suit_char(const char &c)
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
        return 0;
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

