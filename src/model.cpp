#include "model.h"

#include <iostream>

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
    _board.at(c.line).at(c.column).content = p.figure;
}