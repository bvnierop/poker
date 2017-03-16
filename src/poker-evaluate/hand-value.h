#ifndef _HAND_VALUE_H_
#define _HAND_VALUE_H_

#include <cstdint>

#include "hand-eval.h"

namespace poker {

    Rank rank(BitValue value);
    FaceValue major_card(BitValue value, int index = 0);
    uint64_t major_card_count(BitValue value);
    FaceValue minor_card(BitValue value, int index = 0);
    uint64_t minor_card_count(BitValue value);
    Suit value_suit(BitValue value);


    inline __fastcall uint64_t _card_count(BitValue value)
    {
        uint64_t cards = value & RankFaceValuesMask;
        uint64_t count = 0;
        while (cards) {
            cards &= cards - 1;
            ++count;
        }
        return count;
    }

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

#endif // _HAND_VALUE_H_
