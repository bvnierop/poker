#include "../third-party/catch.hpp"
#include "catch-rspec.hpp"
#include "../poker-evaluate/bits.h"

using namespace poker;

Describe("LSB") {
    It("gets the least significant bit") {
        Expect(bsl(0b001010) == 1);
        Expect(bsl(0x8000000000000000) == 63);
    }
}

Describe("MSB") {
    It("gets the most significant bit") {
        Expect(bsr(0b001010) == 3);
        Expect(bsr(0xFFFFFFFFFFFFFFFF) == 63);
    }

}
