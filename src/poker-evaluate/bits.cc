#include "bits.h"

#include <string>
#include <sstream>

namespace poker {
    std::string make_bit_string(uint64_t bits) 
    {
        std::stringstream ss;
        std::string sep = "";
        for (int i = 63; i >= 0; --i) {
            if ((i%4) == 3) {
                ss << sep;
                sep = " ";
            }
            ss << ((bits & (1ull << i)) >> i);
        }
        return ss.str();;
    }
}
