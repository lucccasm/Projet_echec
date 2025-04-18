#pragma once
#include "Piece.h"

namespace model {

class DeplacementTemporaire {
public:
    DeplacementTemporaire(Piece& p, const Position& nouvellePos);
    ~DeplacementTemporaire();

private:
    Piece& piece;
    Position anciennePos;
};

}
