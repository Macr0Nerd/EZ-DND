#pragma once

#include <chrono>
#include <random>

namespace dnd {
    namespace core {
        class dice {
        public:
            dice (int sides) {
                nums = sides;
            }

            ~dice(){}

            int roll(){
                unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
                std::default_random_engine generator (seed);

                std::uniform_int_distribution<int> distribution(1, nums);

                return distribution(generator);
            }

        private:
            int nums;
        };
    }

    core::dice d4 = core::dice(4);
    core::dice d6 = core::dice(6);
    core::dice d8 = core::dice(8);
    core::dice d10 = core::dice(10);
    core::dice d12 = core::dice(12);
    core::dice d20 = core::dice(20);
    core::dice d100 = core::dice(100);
}