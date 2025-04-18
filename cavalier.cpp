#include "Cavalier.h"

namespace model {

std::vector<Position> Cavalier::deplacementsValides() const {
    std::vector<Position> m;
    static const int dr[8] = {2,2,1,1,-1,-1,-2,-2};
    static const int dc[8] = {1,-1,2,-2,2,-2,1,-1};
    auto [r,c] = position;
    for (int i=0;i<8;++i) {
        int nr=r+dr[i], nc=c+dc[i];
        if (nr>=0&&nr<8&&nc>=0&&nc<8) m.emplace_back(nr,nc);
    }
    return m;
}

} // namespace model
