#pragma once

#ifndef DICE_HPP
#define DICE_HPP

#include <chrono>
#include <random>

namespace dnd {
    namespace core {
        class dice {
        public:
            dice (int sides = -1) {
                nums = sides;
            }

            ~dice() = default;

            int roll(){
                if(nums > 0) {
                    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
                    std::default_random_engine generator(seed);

                    std::uniform_int_distribution<int> distribution(1, nums);

                    return distribution(generator);
                } else {
                    return nums;
                }
            }

            dice& operator= (const dice &a) {
                nums = a.nums;

                return *this;
            }

            bool operator== (const dice &a) const {
                return nums == a.nums;
            }

            bool operator!= (const dice &a) const {
                return nums != a.nums;
            }

        private:
            int nums;
        };
    }

    core::dice d0 = core::dice(0);
    core::dice d1 = core::dice(1);
    core::dice d2 = core::dice(2);
    core::dice d4 = core::dice(4);
    core::dice d6 = core::dice(6);
    core::dice d8 = core::dice(8);
    core::dice d10 = core::dice(10);
    core::dice d12 = core::dice(12);
    core::dice d20 = core::dice(20);
    core::dice d100 = core::dice(100);
}

#endif /* DICE_HPP */