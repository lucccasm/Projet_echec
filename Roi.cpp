
/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document est la description de la classe Roi, les mouvements de cette pièce ont été spécifiés.
               De cette façon, le mouvement du roi est propre à lui-même et ne peut pas être confondu avec un autre type de pièce.
*/

#include "Roi.h"

namespace model {

RoiException::RoiException(const char* message) : std::runtime_error(message) {}

int Roi::nombreInstances_ = 0;

Roi::Roi(const Position& positionInitiale, const bool& estBlanc) : Piece(positionInitiale, estBlanc)
{
    if (++nombreInstances_ > 2) {
        --nombreInstances_;
        throw RoiException("Impossible de créer plus de deux rois");
    }
}

Roi::~Roi()
{
    --nombreInstances_;
}

std::vector<Position> Roi::deplacementsValides() const
{
    std::vector<Position> deplacements;
    auto [ligneActuelle, colonneActuelle] = obtenirPosition();

    for (int decalageLigne = -1; decalageLigne <= 1; ++decalageLigne) {
        for (int decalageColonne = -1; decalageColonne <= 1; ++decalageColonne) {
            if (decalageLigne == 0 && decalageColonne == 0)
                continue;

            int nouvelleLigne   = ligneActuelle + decalageLigne;
            int nouvelleColonne = colonneActuelle + decalageColonne;

            if (nouvelleLigne >= 0 && nouvelleLigne < 8
                && nouvelleColonne >= 0 && nouvelleColonne < 8) {
                deplacements.emplace_back(
                    nouvelleLigne,
                    nouvelleColonne
                    );
            }
        }
    }
    return deplacements;
}

}
