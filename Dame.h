#pragma once
#include "Piece.h"

namespace model {

class Dame : public Piece {
public:
    explicit Dame(const Position& positionInitiale);
    std::vector<Position> deplacementsValides() const override;
};

}
