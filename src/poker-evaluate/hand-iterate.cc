#include "hand-iterate.h"

namespace poker {

    void iterate_hands_recursively(int max_cards,
            int num_cards,
            int last_bit,
            uint64_t filter,
            uint64_t cur,
            std::function<void(BitHand)> fn) 
    {
        if (num_cards == max_cards) {
            fn(cur << 4);
            return;
        }

        for (int bit = last_bit + 1; bit < 52; ++bit) {
            if (!(filter & (1ull << bit) << 4)) {
                iterate_hands_recursively(max_cards, num_cards + 1, bit, filter, cur | (1ull << bit), fn);
            }
        }
    }

    void iterate_hands(int max_cards, std::function<void(BitHand)> fn)
    {
        iterate_hands(max_cards, 0, fn);
    }

    void iterate_hands(int max_cards, uint64_t filter, std::function<void(BitHand)> fn)
    {
        iterate_hands_recursively(max_cards, 0, -1, filter, 0, fn);
    }

}
