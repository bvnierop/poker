#include "../third-party/catch.hpp"
#include "catch-rspec.hpp"
#include "../poker-evaluate/hand-parse.h"
#include "../poker-evaluate/hand-iterate.h"

using namespace poker;

Describe("hand iterator") {
    It("iterates all 5-card hands") {
        uint64_t count = 0;
        iterate_hands(5, [&count](BitHand) {
            count++;
        });
        Expect(count == 2598960);
    }

    It("skips filtered cards") {
        uint64_t filter = parse_card("Kh");
        uint64_t mask = 0;

        iterate_hands(5, filter, [&](BitHand hand) {
            mask |= hand;
        });
        Expect((mask & filter) == 0ull);
    }
}
