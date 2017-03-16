#include "../third-party/catch.hpp"
#include "catch-rspec.hpp"
#include "../poker-evaluate/bits.h"

using namespace poker;

Describe("LSB") {
    It("gets the least significant bit") {
        Expect(lsb_index(0b001010) == 1);
        Expect(lsb_index(0x8000000000000000) == 63);
    }
}

Describe("MSB") {
    It("gets the most significant bit") {
        Expect(msb_index(0b001010) == 3);
        Expect(msb_index(0xFFFFFFFFFFFFFFFF) == 63);
    }
}
