#include "hand-eval.h"

#include <vector>
#include <string>
#include <iostream>

#include "hand-value.h"

namespace poker {
    // TODO: move
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

    inline __fastcall BitValue make_rank( Rank rank) {
        return (1ull << to_integral(rank)) << RankOffset; 
    }

    inline __fastcall BitValue add_major_card(BitValue value, uint64_t filtered_hand) {
        return value | (1ull << ((msb_index(filtered_hand) >> 2) - 1)) << MajorCardOffset;
    }

    inline __fastcall BitValue make_value(Rank rank, uint64_t filtered_hand, uint64_t kicker_base, int num_kickers)
    {
            BitValue value = make_rank(rank);
            value = add_major_card(value, filtered_hand);
            value = add_kickers(value, kicker_base, num_kickers);
            return value;
    }

    inline __fastcall uint64_t remove_cards(uint64_t base, uint64_t to_remove)
    {
        return base & ~to_remove;
    }

    inline __fastcall uint64_t remove_highest_card(uint64_t count_indices)
    {
        return remove_cards(count_indices, 1ull << msb_index(count_indices));
    }
    
    inline __fastcall uint64_t count_cards(uint64_t card_mask) 
    {
        card_mask = card_mask - ((card_mask >> 1) & 0x5555555555555555ull);
        card_mask = (card_mask & 0x3333333333333333ull) + ((card_mask >> 2) & 0x3333333333333333ull);
        return ((card_mask + (card_mask >> 4) & 0x0F0F0F0F0F0F0F0Full) * 0x0101010101010101ull) >> 56;
    }

    inline __fastcall uint64_t collapse_hand(BitHand hand)
    {
        hand |= hand >> 1;
        hand |= hand >> 2;
        return hand & 0x1111111111111111ull;
    }

    // note the trailing 0. We zero out the low bits of aces here. 
    static constexpr uint64_t QuadMask = 0x8888888888888880ull;
    static constexpr uint64_t TripletMask = 0x4444444444444440ull;
    static constexpr uint64_t PairMask = 0x2222222222222220ull;
    static constexpr uint64_t FlushMask = 0x1111111111111110ull;
    static constexpr uint64_t StraightMask = 0x11111000000000ull;

    BitValue evaluate_hand(BitHand hand)
    {
        uint64_t count_indices = create_count_indices(hand);

        uint64_t quads = count_indices & QuadMask;
        if (quads) {
            return make_value(Rank::FourOfAKind, quads, remove_cards(count_indices, quads), 1);
        }

        for (int i = 0; i < 4; ++i) {
            uint64_t flush = hand & FlushMask * (1 << i); 
            if (count_cards(flush) >= 5) {
                return make_value(Rank::Flush, flush, remove_highest_card(flush), 4);
            }
        }

        uint64_t suitless_cards = collapse_hand(hand);
        for (int i = 0; i < 10; ++i) {
            uint64_t mask = StraightMask >> (i * 4);
            uint64_t straight = suitless_cards & mask;
            if (straight == mask) {
                return make_value(Rank::Straight, straight, straight, 0);
            }
        }

        uint64_t triplets = count_indices & TripletMask;
        uint64_t pairs = count_indices & PairMask;
        if (triplets) {
            if (pairs) {
                return make_value(Rank::FullHouse, triplets, pairs, 1);
            } else {
                uint64_t next_triplets = remove_highest_card(triplets);
                if (next_triplets) {
                    return make_value(Rank::FullHouse, triplets, next_triplets, 1);
                } else {
                    return make_value(Rank::ThreeOfAKind, triplets, remove_cards(count_indices, triplets), 2);
                }
            }
        } else if (pairs) {
            uint64_t next_pairs = remove_highest_card(pairs);
            if (next_pairs) {
                return add_major_card(make_value(Rank::TwoPair, pairs, remove_cards(count_indices, pairs), 1),
                        next_pairs);
            } else {
                return make_value(Rank::OnePair, pairs, remove_cards(count_indices, pairs), 3);
            }
        }

        return 0;
    }

}

