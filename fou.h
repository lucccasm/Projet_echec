#pragma once
#include "Piece.h"

namespace model {

class Fou : public Piece {
public:
    explicit Fou(const Position& positionInitiale);
    std::vector<Position> deplacementsValides() const override;
};

}

