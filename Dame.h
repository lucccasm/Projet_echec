#pragma once
#include "Piece.h"

namespace model {

class Dame : public Piece {
public:
    explicit Dame(const Position& pos) : Piece(pos) {}
    std::vector<Position> deplacementsValides() const override;
};

} // namespace model
