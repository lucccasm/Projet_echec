/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document est la description de la classe Tour, les mouvements de cette pi�ce ont �t� sp�cifi�s.
               De cette fa�on, le mouvement de la tour est propre � lui-m�me et ne peut pas �tre confondu avec un autre type de pi�ce.
*/

#include "Tour.h"

namespace model {

Tour::Tour(const Position& positionInitiale) : Piece(positionInitiale) {}

std::vector<Position> Tour::deplacementsValides() const
{
    std::vector<Position> deplacements;
    auto [ligneActuelle, colonneActuelle] = positionActuelle;

    for (int i = 0; i < 8; ++i) {
        if (i != ligneActuelle) deplacements.emplace_back(i, colonneActuelle);
        if (i != colonneActuelle) deplacements.emplace_back(ligneActuelle, i);
    }
    return deplacements;
}

}
