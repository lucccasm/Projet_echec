/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document est la description de la classe Tour, les mouvements de cette pièce ont été spécifiés.
               De cette façon, le mouvement de la tour est propre à lui-même et ne peut pas être confondu avec un autre type de pièce.
*/

#include "Tour.h"

namespace model {

Tour::Tour(const Position& positionInitiale, const bool& estBlanc) : Piece(positionInitiale, estBlanc) {}

std::vector<Position> Tour::deplacementsValides() const
{
    std::vector<Position> deplacements;
    auto [ligneActuelle, colonneActuelle] = obtenirPosition();

    for (int i = 0; i < 8; ++i) {
        if (i != ligneActuelle) deplacements.emplace_back(i, colonneActuelle);
        if (i != colonneActuelle) deplacements.emplace_back(ligneActuelle, i);
    }
    return deplacements;
}

}
