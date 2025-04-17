#pragma once
#include <vector>
#include <utility>

namespace model {

using Position = std::pair<int,int>;

class Piece {
public:
    explicit Piece(const Position& pos);
    virtual ~Piece();

    virtual std::vector<Position> deplacementsValides() const = 0;
    const Position& getPosition() const;
    void setPosition(const Position& p);

private:
    Position position;
};

} // namespace model
