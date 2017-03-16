#ifndef _BITS_H_
#define _BITS_H_

#include <cstdint>

namespace poker {

    inline uint64_t __fastcall bsr(const uint64_t &number)
    {
        uint64_t position = 0;
        asm("bsrq %1, %0" : "=r" (position) : "r" (number));
        return position;
    }

    inline uint64_t __fastcall bsl(const uint64_t &number)
    {
        uint64_t position = 0;
        asm("bsf %1, %0" : "=r" (position) : "r" (number));
        return position;
    }

}

#endif // _BITS_H_
