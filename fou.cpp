/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document est la description de la classe Fou, les mouvements de cette pièce ont été spécifiés.
               De cette façon, le mouvement du fou est propre à lui-même et ne peut pas être confondu avec un autre type de pièce.
*/

#include "Fou.h"

namespace model {

Fou::Fou(const Position& positionInitiale) : Piece(positionInitiale){}

std::vector<Position> Fou::deplacementsValides() const
{
    std::vector<Position> deplacements;
    auto [ligneActuelle, colonneActuelle] = positionActuelle;

    for (int decalage = 1; decalage < 8; ++decalage) {
        int hautGaucheL  = ligneActuelle - decalage;
        int hautGaucheC  = colonneActuelle - decalage;
        int hautDroiteL  = ligneActuelle - decalage;
        int hautDroiteC  = colonneActuelle + decalage;
        int basGaucheL   = ligneActuelle + decalage;
        int basGaucheC   = colonneActuelle - decalage;
        int basDroiteL   = ligneActuelle + decalage;
        int basDroiteC   = colonneActuelle + decalage;

        if (hautGaucheL  >= 0 && hautGaucheC  >= 0) deplacements.emplace_back(hautGaucheL,  hautGaucheC);
        if (hautDroiteL  >= 0 && hautDroiteC  <  8) deplacements.emplace_back(hautDroiteL,  hautDroiteC);
        if (basGaucheL   <  8 && basGaucheC   >= 0) deplacements.emplace_back(basGaucheL,   basGaucheC);
        if (basDroiteL   <  8 && basDroiteC   <  8) deplacements.emplace_back(basDroiteL,  basDroiteC);
    }
    return deplacements;
}

}
