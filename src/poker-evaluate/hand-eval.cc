#include "hand-eval.h"

#include <vector>
#include <string>

namespace poker {
    bool is_value_char(const char& c) 
    {
        static const std::string values("23456789TJQKAtjkqa");
        return values.find(c) != values.npos;
    }
    
    bool is_face_char(const char &c)
    {
        static const std::string faces("hcdsHCDS");
        return faces.find(c) != faces.npos;
    }

    BitHand parse_hand(const std::string &description)
    {
        BitHand hand = 0;
        for (size_t i = 0; i < description.size(); ++i) {
            char a = description[i];
            char b = description[i+1];
            if (is_value_char(a) && is_face_char(b))  {
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
        return Rank::None;
    }

    BitCard parse_card(const std::string &description)
    {
        static constexpr uint64_t values[] = {
           0, /* 0 */ 0, /* 1 */
           to_integral(Value::Two),
           to_integral(Value::Three),
           to_integral(Value::Four),
           to_integral(Value::Five),
           to_integral(Value::Six),
           to_integral(Value::Seven),
           to_integral(Value::Eight),
           to_integral(Value::Nine),
           0, /* : */ 0, /* ; */ 0, /* < */ 0, /* = */ 0, /* > */ 0, /* ? */ 0, /* @ */
           to_integral(Value::Ace),
           0, /* B */ 0, /* C */ 0, /* D */ 0, /* E */ 0, /* F */ 0, /* G */ 0, /* H */ 0, /* I */
           to_integral(Value::Jack),
           to_integral(Value::King),
           0, /* L */ 0, /* M */ 0, /* N */ 0, /* O */ 0, /* P */
           to_integral(Value::Queen),
           0, /* R */ 0, /* S */
           to_integral(Value::Ten),
           0, /* U */ 0, /* V */ 0, /* W */ 0, /* X */ 0, /* Y */ 0, /* Z */ 0, /* [ */ 0, /* \ */
           0, /* ] */ 0, /* ^ */ 0, /* _ */ 0, /* ` */
           to_integral(Value::Ace),
           0, /* b */ 0, /* c */ 0, /* d */ 0, /* e */ 0, /* f */ 0, /* g */ 0, /* h */ 0, /* i */
           to_integral(Value::Jack),
           to_integral(Value::King),
           0, /* l */ 0, /* m */ 0, /* n */ 0, /* o */ 0, /* p */
           to_integral(Value::Queen),
           0, /* r */ 0, /* s */
           to_integral(Value::Ten),
        };

        static constexpr uint64_t faces[] = {
           0, /* A */ 0, /* B */ to_integral(Face::Clubs), /* C */ to_integral(Face::Diamonds), /* D */ 0, /* E */
           0, /* F */ 0, /* G */ to_integral(Face::Hearts), /* H */ 0, /* I */ 0, /* J */
           0, /* K */ 0, /* L */ 0, /* M */ 0, /* N */ 0, /* O */
           0, /* P */ 0, /* Q */ 0, /* R */ to_integral(Face::Spades), /* S */ 0, /* T */
           0, /* U */ 0, /* V */ 0, /* W */ 0, /* X */ 0, /* Y */
           0, /* Z */
           0, /* [ */ 0, /* \ */ 0, /* ] */ 0, /* ^ */ 0, /* _ */ 0, /* ` */
           0, /* a */ 0, /* b */ to_integral(Face::Clubs), /* c */ to_integral(Face::Diamonds), /* d */ 0, /* e */
           0, /* f */ 0, /* g */ to_integral(Face::Hearts), /* h */ 0, /* i */ 0, /* j */
           0, /* k */ 0, /* l */ 0, /* m */ 0, /* n */ 0, /* o */
           0, /* p */ 0, /* q */ 0, /* r */ to_integral(Face::Spades), /* s */ 0, /* t */
           0, /* u */ 0, /* v */ 0, /* w */ 0, /* x */ 0, /* y */ 0,
           /* z */
        };

        uint64_t face = faces[(int)description[1] - 'A'];
        uint64_t value = values[(int)description[0] - '0'];

        return (1ull << face) << 
            (value << 2);
    }

}
