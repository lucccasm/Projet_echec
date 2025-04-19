#pragma once
#include "Piece.h"

namespace model {

class Pion : public Piece {
public:
    Pion(const Position& positionInitiale, bool estBlanche);
    std::vector<Position> deplacementsValides() const override;

private:
    bool estBlanche;
};

}
