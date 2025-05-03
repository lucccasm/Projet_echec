/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document est la description de la classe Dame, les mouvements de cette pièce ont été spécifiés.
               De cette façon, le mouvement de la dame est propre à lui-même et ne peut pas être confondu avec un autre type de pièce.
*/


#include "Dame.h"
#include "Tour.h"
#include "Fou.h"

namespace model {

Dame::Dame(const Position& positionInitiale, const bool& estBlanc) : Piece(positionInitiale, estBlanc) {}

std::vector<Position> Dame::deplacementsValides() const
{
    std::vector<Position> mouvementsTour = Tour(obtenirPosition(), obtenirEstBlanc()).deplacementsValides();
    std::vector<Position> mouvementsFou  = Fou(obtenirPosition(), obtenirEstBlanc()).deplacementsValides();

    mouvementsTour.insert(
        mouvementsTour.end(),
        mouvementsFou.begin(),
        mouvementsFou.end()
        );
    return mouvementsTour;
}

}
