#include "../third-party/catch.hpp"
#include "catch-rspec.hpp"
#include "../poker-evaluate/bits.h"

#include <sstream>

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

Describe("make_bit_string") {
    It("creates a human readable bit string") {
        Expect(make_bit_string(0b1111011110111101011100110101011010011010110000010010010010000000) == 
                    "1111 0111 1011 1101 0111 0011 0101 0110 1001 1010 1100 0001 0010 0100 1000 0000");
    }

    It("streams a human readable bit string") {
        std::stringstream ss;
        stream_bit_string(0b1111011110111101011100110101011010011010110000010010010010000000, ss);
        Expect(ss.str() == "1111 0111 1011 1101 0111 0011 0101 0110 1001 1010 1100 0001 0010 0100 1000 0000");
    }
}
