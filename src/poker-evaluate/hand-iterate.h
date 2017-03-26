#ifndef _HAND_ITERATE_H_
#define _HAND_ITERATE_H_

#include <functional>

#include "types.h"

namespace poker 
{
    void iterate_hands(int max_cards, std::function<void(BitHand)>);
    void iterate_hands(int max_cards, uint64_t filter, std::function<void(BitHand)>);
}

#endif // __HAND_ITERATE_H_

