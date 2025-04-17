#include "Roi.h"

namespace model {

int Roi::compteurInstances = 0;

RoiException::RoiException(const char* msg)
    : std::runtime_error(msg)
{
}

Roi::Roi(const Position& pos)
    : Piece(pos)
{
    if (++compteurInstances > 2) {
        --compteurInstances;
        throw RoiException("Trop de rois instanci\xc3\xa9s");
    }
}

Roi::~Roi() {
    --compteurInstances;
}

std::vector<Position> Roi::deplacementsValides() const {
    std::vector<Position> moves;
    auto [ligne, colonne] = getPosition();
    for (int dL = -1; dL <= 1; ++dL) {
        for (int dC = -1; dC <= 1; ++dC) {
            if (dL == 0 && dC == 0) continue;
            int newL = ligne + dL;
            int newC = colonne + dC;
            if (newL >= 0 && newL < 8 && newC >= 0 && newC < 8) {
                moves.emplace_back(newL, newC);
            }
        }
    }
    return moves;
}

} // namespace model
