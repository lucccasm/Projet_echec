#pragma once
#include "Piece.h"

namespace model {

class Fou : public Piece {
public:
    explicit Fou(const Position& pos) : Piece(pos) {}
    std::vector<Position> deplacementsValides() const override;
};

} // namespace model

