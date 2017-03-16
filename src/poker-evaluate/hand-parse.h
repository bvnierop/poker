#ifndef _HAND_PARSE_H_
#define _HAND_PARSE_H_

#include "hand-eval.h"

namespace poker {

    bool is_value_char(const char& c);
    bool is_suit_char(const char &c);

    BitHand parse_hand(const std::string &description);
    BitCard parse_card(const std::string &description);

}

#endif // _HAND_PARSE_H_
