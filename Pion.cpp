#include "Pion.h"

namespace model {

Pion::Pion(const Position& positionInitiale, bool estBlanche) : Piece(positionInitiale), estBlanche(estBlanche) {}

std::vector<Position> Pion::deplacementsValides() const
{
    std::vector<Position> deplacements;
    auto [ligneActuelle, colonneActuelle] = positionActuelle;

    int direction = estBlanche ? 1 : -1;
    int ligneDevant = ligneActuelle + direction;

    if (ligneDevant >= 0 && ligneDevant < 8) {
        deplacements.emplace_back(ligneDevant, colonneActuelle);

        bool enPositionInitiale =
            (estBlanche && ligneActuelle == 1) ||
            (!estBlanche && ligneActuelle == 6);

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
