/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document est la description de la classe Pi�ce. La pi�ce a donc une position
				initiale et une position actuelle. La pi�ce est la classe m�re de toutes les pi�ces.
*/

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
