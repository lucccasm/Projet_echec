/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document est la description de la classe Cavalier, les mouvements de cette pièce ont été spécifiés.
               De cette façon, le mouvement du cavalier est propre à lui-même et ne peut pas être confondu avec un autre type de pièce.
*/


#include "Cavalier.h"

namespace model {

Cavalier::Cavalier(const Position& positionInitiale, const bool& estBlanc) : Piece(positionInitiale, estBlanc) {}

std::vector<Position> Cavalier::deplacementsValides() const
{
    std::vector<Position> deplacements;
    static const int deplacementsLigne[8] = { 2,  2,  1,  1, -1, -1, -2, -2 };
    static const int deplacementsCol[8]   = { 1, -1,  2, -2,  2, -2,  1, -1 };

    auto [ligneActuelle, colonneActuelle] = obtenirPosition();

    for (int i = 0; i < 8; ++i) {
        int nouvelleLigne   = ligneActuelle + deplacementsLigne[i];
        int nouvelleColonne = colonneActuelle + deplacementsCol[i];

        if (nouvelleLigne >= 0 && nouvelleLigne < 8
            && nouvelleColonne >= 0 && nouvelleColonne < 8) {
            deplacements.emplace_back(
                nouvelleLigne,
                nouvelleColonne
                );
        }
    }
    return deplacements;
}

}
