#include "DeplacementTemporaire.h"

namespace model {

DeplacementTemporaire::DeplacementTemporaire(Piece& p, const Position& nouvellePos)
    : piece(p), anciennePos(p.getPosition())
{
    piece.setPosition(nouvellePos);
}

DeplacementTemporaire::~DeplacementTemporaire() {
    piece.setPosition(anciennePos);
}

}
