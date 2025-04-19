#include "DeplacementTemporaire.h"

namespace model {

DeplacementTemporaire::DeplacementTemporaire(Piece& piece, const Position& positionTemporaire )
    : pieceReference(piece), positionOriginale(piece.obtenirPosition())
{
    pieceReference.definirPosition(positionTemporaire);
}

DeplacementTemporaire::~DeplacementTemporaire()
{
    pieceReference.definirPosition(positionOriginale);
}

}
