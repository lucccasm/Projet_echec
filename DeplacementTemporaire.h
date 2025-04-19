#pragma once
#include "Piece.h"

namespace model {

class DeplacementTemporaire {
public:
    DeplacementTemporaire(Piece& piece, const Position& positionTemporaire);
    ~DeplacementTemporaire();

private:
    Piece& pieceReference;
    Position  positionOriginale;
};

}
