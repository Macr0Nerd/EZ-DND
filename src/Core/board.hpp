#pragma once

#ifndef EZDND_BOARD_HPP
#define EZDND_BOARD_HPP

#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include "Character/character.hpp"

namespace dnd::core {
    class board {
    public:
        explicit board(int height = 12, int width = 12) : h(height), w(width) {
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


        ///Serialization/Deserialization functions
        void save(const std::string& file) {
            std::ofstream out;
            out.open(file);

            if(out.good()) {
                out << h << "," << w << "\n";

                for(auto &i : b) {
                    for(auto &j : i) {
                        if(j.uid) {
                            out << j.uid << ":";

                            std::pair<int, int> x = getPos(j.uid);

                            out << x.first << "," << x.second << "\n";
                        }
                    }
                }

                out.flush();
                out.close();

                std::cout << "WRITTEN" << std::endl;
            } else {
                std::cerr << "CAN'T WRITE" << std::endl;
            }
        }

        void load(const std::string& file, std::vector<character> z) {
            std::ifstream fin;
            fin.open(file);
            std::string tmp;
            int token, x;
            std::string delim1 = ":"; std::string delim2 = ",";

            if(fin.good()) {
                tmp.clear();
                getline(fin, tmp);
                h = std::stoi(tmp.substr(0, tmp.find(delim2)));
                tmp.erase(0, tmp.find(delim2) + delim2.length());
                w = std::stoi(tmp);

                refresh();

                while(!fin.eof()) {
                    tmp.clear();
                    getline(fin, tmp);

                    if(tmp.empty()) {
                        break;
                    }

                    token = std::stoi(tmp.substr(0, tmp.find(delim1)));
                    tmp.erase(0, tmp.find(delim1) + delim1.length());
                    x = std::stoi(tmp.substr(0, tmp.find(delim2)));
                    tmp.erase(0, tmp.find(delim2) + delim2.length());

                    for(auto &i : z) {
                        if(i.uid == token) {
                            place(i, x, std::stoi(tmp));
                        }
                    }
                }

                std::cout << "READ" << std::endl;
            } else {
                std::cerr << "CAN'T READ" << std::endl;
            }

            fin.close();
        }


        void place(const character& z, int x, int y) {
            if(b[x][y].uid == 0){
                b[x][y] = z;
            }
        }

        std::pair<int, int> getPos(const unsigned long id) {
            for(unsigned long i = 0; i < b.size(); ++i) {
                for (unsigned long j = 0; j < b[i].size(); ++j) {
                    if (b[i][j].uid == id) {
                        return {i, j};
                    }
                }
            }

            return {-1, -1};
        }

        character& getChar(int x, int y) {
            return b[x][y];
        }

        std::vector<character> getAdjacent(const unsigned long id) {
            std::pair<int, int> pos = getPos(id);
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

        void move (const unsigned long id, int x, int y) {
            std::pair<int, int> pos = getPos(id);

            if(b[x][y].getName() == "EMPTY") {
                std::swap(b[pos.first][pos.second], b[x][y]);
            }
        }

        std::vector<std::vector<character> > getBoard() {
            return b;
        }

    private:
        int h, w;
        std::vector<std::vector<character> > b;

    private:
        void refresh() {
            std::vector<character> tmp;
            tmp.assign(h, character("EMPTY", "EMPTY", "EMPTY", "EMPTY", 0, 0, 0, 0, 0, 0, 0, true));

            b.assign(w, tmp);
        }
    };
}

#endif /* EZDND_BOARD_HPP */
