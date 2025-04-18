#include "Dame.h"
#include "Tour.h"
#include "Fou.h"

namespace model {

std::vector<Position> Dame::deplacementsValides() const {
    // Combine Rook and Bishop
    std::vector<Position> m;
    auto rook = Tour(position).deplacementsValides();
    auto bishop = Fou(position).deplacementsValides();
    m.insert(m.end(), rook.begin(), rook.end());
    m.insert(m.end(), bishop.begin(), bishop.end());
    return m;
}

} // namespace model
