#ifndef _HAND_EVAL_H_
#define _HAND_EVAL_H_

#include <string>
#include <functional>
#include <map>
#include <unordered_map>

#include "types.h"
#include "bits.h"


namespace poker 
{
    BitValue evaluate_hand(BitHand hand);
    BitValue evaluate_hand_fast(BitHand hand);
}

#endif

