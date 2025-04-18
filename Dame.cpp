#include "Dame.h"
#include "Tour.h"
#include "Fou.h"

namespace model {

Dame::Dame(const Position& pos) : Piece(pos) {}

std::vector<Position> Dame::deplacementsValides() const {

    std::vector<Position> mouvements;
    auto tour = Tour(position).deplacementsValides();
    auto fou = Fou(position).deplacementsValides();
    mouvements.insert(mouvements.end(), tour.begin(), tour.end());
    mouvements.insert(mouvements.end(), fou.begin(), fou.end());
    return mouvements;
}

}
