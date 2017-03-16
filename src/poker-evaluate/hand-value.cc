#include "hand-value.h"

namespace poker {

    Rank rank(BitValue value)
    {
        return to_enum<Rank>(msb_index(value >> RankOffset));
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
        return to_enum<Suit>(msb_index((value >> SuitOffset) & 0xF));
    }

}
