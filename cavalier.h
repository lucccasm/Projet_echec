#pragma once
#include "Piece.h"

namespace model {

class Cavalier : public Piece {
public:
    explicit Cavalier(const Position& pos) : Piece(pos) {}
    std::vector<Position> deplacementsValides() const override;
};

} // namespace model
