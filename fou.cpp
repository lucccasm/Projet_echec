#include "Fou.h"

namespace model {

std::vector<Position> Fou::deplacementsValides() const {
    std::vector<Position> m;
    auto [r,c] = position;
    for (int d=1; d<8; ++d) {
        if (r+d<8&&c+d<8) m.emplace_back(r+d,c+d);
        if (r+d<8&&c-d>=0) m.emplace_back(r+d,c-d);
        if (r-d>=0&&c+d<8) m.emplace_back(r-d,c+d);
        if (r-d>=0&&c-d>=0) m.emplace_back(r-d,c-d);
    }
    return m;
}

} // namespace model
