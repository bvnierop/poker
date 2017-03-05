#include "../third-party/catch.hpp"
#include "catch-rspec.hpp"
#include "../poker-evaluate/hand-eval.h"

Describe("hand eval") {
    It("returns 42") {
        Expect(hand_eval() == 42);
    }
}

