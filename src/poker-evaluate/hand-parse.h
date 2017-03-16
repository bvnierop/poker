#ifndef _HAND_PARSE_H_
#define _HAND_PARSE_H_

#include "hand-eval.h"

namespace poker {

    bool is_value_char(const char& c);
    bool is_suit_char(const char &c);

    BitHand parse_hand(const std::string &description);
    BitCard parse_card(const std::string &description);

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
}

#endif // _HAND_PARSE_H_
