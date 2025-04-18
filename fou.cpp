#include "Fou.h"

namespace model {

Fou::Fou(const Position& pos) : Piece(pos) {}

std::vector<Position> Fou::deplacementsValides() const {
    std::vector<Position> mouvements;
    auto [r,c] = position;

    for (int d = 1; d < 8; ++d) {
        if (r + d < 8 && c + d < 8) mouvements.emplace_back(r + d, c + d);
        if (r + d < 8 && c - d >= 0) mouvements.emplace_back(r + d, c - d);
        if (r - d >= 0 && c + d < 8) mouvements.emplace_back(r - d, c + d);
        if (r - d >= 0 && c - d >= 0) mouvements.emplace_back(r - d, c - d);
    }

    return mouvements;
}

}
