#include "Tour.h"

namespace model {

Tour::Tour(const Position& pos) : Piece(pos) {}

std::vector<Position> Tour::deplacementsValides() const {
    std::vector<Position> mouvements;
    auto [r,c] = position;

    for (int i = 0; i < 8; ++i) {
        if (i != r) mouvements.emplace_back(i, c);
        if (i != c) mouvements.emplace_back(r, i);
    }

    return mouvements;
}

}
