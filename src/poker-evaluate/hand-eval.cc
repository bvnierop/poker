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

    inline __fastcall uint64_t create_count_indices(BitHand hand)
    {
        uint64_t count_indices = 0;
        for (uint64_t temp = hand; temp; temp &= (temp - 1)) {
            uint64_t nibble_offset = (lsb_index(temp) >> 2) << 2; 

            // zero out everything but the nibble and increment its index by shifting to the left
            uint64_t nibble = ((count_indices >> nibble_offset) & 0xFull) << 1ull; 
            bool nibble_is_zero = nibble == 0;

            // if the nibble is zero, set it to 1, because shifting zero doesn't
            // doesn't result in 0b0001
            nibble = (nibble & ~0x1) | (-nibble_is_zero & 0x1); 

            // reset the nibble in count_indices to zero
            count_indices &= (0xFFFFFFFFFFFFFFFFull ^ (0xFull << nibble_offset)); 

            // put the new nibble with incremented bit index in place
            count_indices |= nibble << nibble_offset; 
        }
        return count_indices;
    }

    inline __fastcall BitValue add_kickers(BitValue value, uint64_t kickers, int amount)
    {
        for (int i = 0; i < amount; ++i) {
            value |= 1ull << ((msb_index(kickers) >> 2) - 1);
            kickers &= ~(1ull << msb_index(kickers));
        }
        return value;
    }

    BitValue evaluate_hand(BitHand hand)
    {
        BitValue value = 0;

        uint64_t count_indices = create_count_indices(hand);

        uint64_t quads = count_indices & 0x8888888888888888ull;
        if (quads) {
            value |= (1ull << to_integral(Rank::FourOfAKind)) << RankOffset;
            value |= (1ull << ((msb_index(quads) >> 2) - 1)) << MajorCardOffset;
            value = add_kickers(value, count_indices & ~quads, 1);
        }

        // This looks like duplication, but triplets can branch into
        // Full House, while quads cannot. Since speed matters, we
        // really don't want the additional assignment, AND and conditional
        // that extracting a function would incur.
        uint64_t triplets = count_indices & 0x4444444444444444ull;
        if (triplets) {
            value |= (1ull << to_integral(Rank::ThreeOfAKind)) << RankOffset; 
            value |= (1ull << ((msb_index(triplets) >> 2) - 1)) << MajorCardOffset;
            value = add_kickers(value, count_indices & ~triplets, 2);
        }

        return value;
    }

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

