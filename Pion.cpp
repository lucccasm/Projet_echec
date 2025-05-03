/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document est la description de la classe Pion, les mouvements de cette pièce ont été spécifiés.
               De cette façon, le mouvement du pion est propre à lui-même et ne peut pas être confondu avec un autre type de pièce.
*/

#include "Pion.h"

namespace model {

Pion::Pion(const Position& positionInitiale, bool estBlanc) : Piece(positionInitiale, estBlanc){}

std::vector<Position> Pion::deplacementsValides() const
{
    std::vector<Position> deplacements;
    auto [ligneActuelle, colonneActuelle] = obtenirPosition();

    int direction = obtenirEstBlanc() ? -1 : +1;
    int ligneDevant = ligneActuelle + direction;

    if (ligneDevant >= 0 && ligneDevant < 8) {
        deplacements.emplace_back(ligneDevant, colonneActuelle);

        bool enPositionInitiale =
            (obtenirEstBlanc() && ligneActuelle == 6) ||
            (!obtenirEstBlanc() && ligneActuelle == 1);

        if (enPositionInitiale) {
            int deuxCases = ligneActuelle + 2 * direction;
            if (deuxCases >= 0 && deuxCases < 8)
            {
                deplacements.emplace_back(deuxCases, colonneActuelle);
            }
        }
    }

    for (int decalageColonne : { -1, +1 }) {
        int colonneDiagonale = colonneActuelle + decalageColonne;
        if (ligneDevant >= 0 && ligneDevant < 8
            && colonneDiagonale >= 0 && colonneDiagonale < 8)
        {
            deplacements.emplace_back(ligneDevant, colonneDiagonale);
        }
    }

    return deplacements;
}

}
