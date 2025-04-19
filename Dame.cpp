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
