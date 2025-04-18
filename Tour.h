#pragma once
#include "Piece.h"

namespace model {

class Tour : public Piece {
public:
    explicit Tour(const Position& pos) : Piece(pos) {}
    std::vector<Position> deplacementsValides() const override;
};

} // namespace model

