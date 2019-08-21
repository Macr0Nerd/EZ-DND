#pragma once

#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <map>
#include "Character/character.hpp"

namespace dnd::core {
    class board {
    public:
        explicit board(int height = 12, int width = 12) {
                std::vector<character> tmp;
                tmp.assign(height, character("EMPTY", "EMPTY", "EMPTY", "EMPTY", 0, 0, 0, 0, 0, 0, 0, true));

                b.assign(width, tmp);
            }

        ~board() = default;

        board& operator= (const board &a) = default;

        bool operator== (const board &a) {
            return b == a.b;
        }

        bool operator!= (const board &a) {
            return b != a.b;
        }


        void place(const character& z, int x, int y) {
            if(b[x][y].getName() == "EMPTY"){
                b[x][y] = z;
            }
        }

        std::pair<int, int> getPos(const character& z) {
            for(unsigned long i = 0; i < b.size(); ++i) {
                auto it = std::find(b[i].begin(), b[i].end(), z);

                if(it != b[i].end()) {
                    return {i, std::distance(b[i].begin(), it)};
                }
            }

            return {-1, -1};
        }

        std::vector<character> getAdjacent(const character& z) {
            std::pair<int, int> pos = getPos(z);
            std::vector<character> tmp;

            for (int i = -1; i < 2; ++i) {
                for (int j = -1; j < 2; ++j) {
                    if(i == 0 && j == 0){
                        continue;
                    }

                    try {
                        if(b[pos.first + i][pos.second + j].getName() == "EMPTY"){
                            continue;
                        } else {
                            tmp.push_back(b[pos.first + i][pos.second + j]);
                        }
                    } catch(const std::out_of_range&) {
                        continue;
                    }
                }
            }

            return tmp;
        }

        void move (const character& z, int x, int y) {
            std::pair<int, int> pos = getPos(z);

            if(b[x][y].getName() == "EMPTY") {
                std::swap(b[pos.first][pos.second], b[x][y]);
            }
        }

        std::vector<std::vector<character> > getBoard() {
            return b;
        }

    private:
        std::vector<std::vector<character> > b;
    };
}

#endif /* BOARD_HPP */
