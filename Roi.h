#pragma once
#include "Piece.h"
#include <stdexcept>

namespace model {

class RoiException : public std::runtime_error {
public:
    explicit RoiException(const char* message);
};

class Roi : public Piece {
public:
    explicit Roi(const Position& positionInitiale);
    ~Roi() override;

    std::vector<Position> deplacementsValides() const override;

private:
    static int nombreInstances;
};

}
