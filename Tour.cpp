#include "Tour.h"

namespace model {

std::vector<Position> Tour::deplacementsValides() const {
    std::vector<Position> m;
    auto [r,c] = position;
    for (int i=0;i<8;++i) {
        if (i!=r) m.emplace_back(i,c);
        if (i!=c) m.emplace_back(r,i);
    }
    return m;
}

} // namespace model
