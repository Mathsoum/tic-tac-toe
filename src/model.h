#ifndef MODEL_H_
#define MODEL_H_

#include <array>
#include <iostream>

enum class Figure { EMPTY = 0, CROSS, CIRCLE };

struct Player {
    Figure figure;
};

struct Coord {
    unsigned int line = 0;
    unsigned int column = 0;
};

struct Square {
    Coord coord;
    Figure content = Figure::EMPTY;
};

std::ostream& operator<<(std::ostream& in, const Coord& c);

class Game {
    std::array<std::array<Square, 3>, 3> _board;

public:
    explicit Game();
    void print_board() const;
    void play(const Player& p, const Coord& c);
    bool finished() const;
    bool is_winner(const Player& p) const;
};

#endif