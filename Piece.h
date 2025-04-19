#pragma once
#include <vector>
#include <utility>

namespace model {
using Position = std::pair<int, int>;

class Piece {
public:
    explicit Piece(const Position& positionInitiale);
    virtual ~Piece();

    virtual std::vector<Position> deplacementsValides() const = 0;
    const Position& obtenirPosition() const;
    void definirPosition(const Position& nouvellePosition);

protected:
    Position positionActuelle;
};
}
