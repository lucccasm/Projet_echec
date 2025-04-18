#include "Pion.h"

namespace model {

Pion::Pion(const Position& pos, bool estBlanc)
    : Piece(pos), blanc(estBlanc)
{}

std::vector<Position> Pion::deplacementsValides() const {
    std::vector<Position> m;
    auto [r,c] = position;
    int dir = blanc ? 1 : -1;
    // Avancer d'une case
    if (r+dir>=0 && r+dir<8) {
        m.emplace_back(r+dir,c);
        // Déplacement initial de deux cases
        if ((blanc && r==1) || (!blanc && r==6)) {
            if (r+2*dir>=0 && r+2*dir<8)
                m.emplace_back(r+2*dir,c);
        }
    }
    // Captures diagonales
    for (int dc : {-1,1}) {
        int nc = c+dc, nr = r+dir;
        if (nr>=0 && nr<8 && nc>=0 && nc<8)
            m.emplace_back(nr,nc);
    }
    return m;
}

} // namespace model
