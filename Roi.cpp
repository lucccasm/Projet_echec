#include "Roi.h"

namespace model {

RoiException::RoiException(const char* msg): std::runtime_error(msg){}

int Roi::compteurInstances = 0;

Roi::Roi(const Position& pos): Piece(pos)
{
    if (++compteurInstances > 2) {
        --compteurInstances;
        throw RoiException("Trop de rois instanciés");
    }
}

Roi::~Roi() {
    --compteurInstances;
}

std::vector<Position> Roi::deplacementsValides() const {
    std::vector<Position> mouvements;
    auto [r,c] = position;

    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc =- 1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;
            int nr = r + dr;
            int nc = c + dc;
            if (nr >= 0 && nr < 8 && nc >= 0 && nc < 8) {
                mouvements.emplace_back(nr,nc);
            }
        }
    }

    return mouvements;
}

}
