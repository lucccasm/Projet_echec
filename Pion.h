#pragma once
#include "Piece.h"

namespace model {

class Pion : public Piece {
public:
    Pion(const Position& pos, bool estBlanc);
    std::vector<Position> deplacementsValides() const override;

private:
    bool blanc;
};

} // namespace model

