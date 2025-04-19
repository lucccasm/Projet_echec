#pragma once
#include "Piece.h"

namespace model {

class Cavalier : public Piece {
public:
    explicit Cavalier(const Position& positionInitiale);
    std::vector<Position> deplacementsValides() const override;
};

}
