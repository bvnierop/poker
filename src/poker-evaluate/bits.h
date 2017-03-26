#ifndef _BITS_H_
#define _BITS_H_

#include <cstdint>
#include <string>

namespace poker {

    inline uint64_t __fastcall msb_index(const uint64_t &number)
    {
        uint64_t position = 0;
        asm("bsrq %1, %0" : "=r" (position) : "r" (number));
        return position;
    }

    inline uint64_t __fastcall lsb_index(const uint64_t &number)
    {
        uint64_t position = 0;
        asm("bsf %1, %0" : "=r" (position) : "r" (number));
        return position;
    }

    std::string make_bit_string(uint64_t bits);
    void stream_bit_string(uint64_t bits, std::ostream &stream);
}

#endif // _BITS_H_
