/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document est la description de la classe Dame, les mouvements de cette pi�ce ont �t� sp�cifi�s.
               De cette fa�on, le mouvement de la dame est propre � lui-m�me et ne peut pas �tre confondu avec un autre type de pi�ce.
*/


#include "Dame.h"
#include "Tour.h"
#include "Fou.h"

namespace model {

Dame::Dame(const Position& positionInitiale) : Piece(positionInitiale) {}

std::vector<Position> Dame::deplacementsValides() const
{
    std::vector<Position> mouvementsTour = Tour(positionActuelle).deplacementsValides();
    std::vector<Position> mouvementsFou  = Fou(positionActuelle).deplacementsValides();

    mouvementsTour.insert(
        mouvementsTour.end(),
        mouvementsFou.begin(),
        mouvementsFou.end()
    );
    return mouvementsTour;
}

}
