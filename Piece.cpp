#include "Piece.h"

namespace model {

Piece::Piece(const Position& positionInitiale): positionActuelle(positionInitiale) {}

Piece::~Piece() = default;

const Position& Piece::obtenirPosition() const
{
    return positionActuelle;
}

void Piece::definirPosition(const Position& nouvellePosition)
{
    positionActuelle = nouvellePosition;
}

}
