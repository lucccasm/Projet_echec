#pragma once
#include "Piece.h"

namespace model {

// RAII pour déplacer temporairement une pièce
class DeplacementTemporaire {
public:
    DeplacementTemporaire(Piece& p, const Position& nouvellePos);
    ~DeplacementTemporaire();

private:
    Piece& piece;
    Position anciennePos;
};

} // namespace model
