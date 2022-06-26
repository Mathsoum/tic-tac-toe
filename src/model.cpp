#include "model.h"

#include <algorithm>

std::ostream& operator<<(std::ostream& in, const Coord& c) {
    in << "{" << c.line << "," << c.column << "}";
    return in;
}

Game::Game() {
    auto line_nb = 0U;
    for (auto& line : _board) {
        auto column_nb = 0U;
        for (auto& square : line) {
            square.coord.line = line_nb;
            square.coord.column = column_nb;
            ++column_nb;
        }
        ++line_nb;
    }
}

void Game::print_board() const {
    for (const auto& line : _board) {
        std::cout << " |";
        for (const auto& square : line) {
            std::cout << " <";
            switch (square.content) {
                case Figure::CIRCLE:
                std::cout << "X";
                break;
                case Figure::CROSS:
                std::cout << "O";
                break;
                default:
                std::cout << " ";
                break;
            }
            std::cout << "> ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

void Game::play(const Player& p, const Coord& c) {
    if (c.line >= _board.size()) {
        std::cerr << "Invalid coordinates. Line " << c.line << " is out of bounds!" << std::endl;
        return;
    }
    if (c.column >= _board.at(0).size()) {
        std::cerr << "Invalid coordinates. Column " << c.column << " is out of bounds!" << std::endl;
        return;
    }

    if (_board.at(c.line).at(c.column).content != Figure::EMPTY) {
        std::cerr << "Square at " << c << " is already filled!" << std::endl;
        return;
    }
    _board.at(c.line).at(c.column).content = p.figure;
}

bool Game::finished() const {
    return std::all_of(_board.begin(), _board.end(), [](const auto& line) {
        return std::all_of(line.begin(), line.end(), [](const auto& square) { return (square.content != Figure::EMPTY); });
    });
}

bool Game::is_winner(const Player& p) const {
    if (!finished())
        return false;

    auto line_win = std::any_of(_board.begin(), _board.end(), [p](const auto& line) {
        return std::all_of(line.begin(), line.end(), [p](const auto& square) { return (square.content != p.figure); });
    });
    if (line_win)
        return true;

    const auto& line0 = _board.at(0);
    const auto& line1 = _board.at(1);
    const auto& line2 = _board.at(2);
    auto column_win = false;
    for (auto col_idx = 0U; (col_idx < 3) || column_win; ++col_idx) {
        column_win = line0.at(col_idx).content == p.figure
                     && line1.at(col_idx).content == p.figure
                     && line2.at(col_idx).content == p.figure;
    }
    if (column_win)
        return true;

    //TODO diag win
}