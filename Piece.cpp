#include "Piece.h"

namespace model {

Piece::Piece(const Position& pos) : position(pos) {}

Piece::~Piece() = default;

const Position& Piece::getPosition() const {
    return position;
}

void Piece::setPosition(const Position& p) {
    position = p;
}

}
