#pragma once
#include "Piece.h"
#include <stdexcept>

namespace model {

// Exception lançée si plus de 2 rois sont instanciés
class RoiException : public std::runtime_error {
public:
    explicit RoiException(const char* msg);
};

class Roi : public Piece {
public:
    explicit Roi(const Position& pos);
    ~Roi() override;

    std::vector<Position> deplacementsValides() const override;

private:
    static int compteurInstances;
};

} // namespace model
