/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document est la description de la classe Pièce. La pièce a donc une position
                initiale et une position actuelle. La pièce est la classe mère de toutes les pièces.
*/

#include "Piece.h"

namespace model {

Piece::Piece(const Position& positionInitiale, const bool& estBlanc)
    : positionActuelle_(positionInitiale),estBlanc_(estBlanc) {}

Piece::~Piece() = default;

const Position& Piece::obtenirPosition() const
{
    return positionActuelle_;
}

const bool& Piece::obtenirEstBlanc() const
{
    return estBlanc_;
}

void Piece::definirPosition(const Position& nouvellePosition)
{
    positionActuelle_ = nouvellePosition;
}

}
