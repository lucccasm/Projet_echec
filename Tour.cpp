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
