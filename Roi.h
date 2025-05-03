/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document est la description de la classe Roi, les mouvements de cette pièce ont été spécifiés.
               De cette façon, le mouvement du roi est propre à lui-même et ne peut pas être confondu avec un autre type de pièce.
*/
// ATTENTION : Il semble que beaucoup de warnings apparaissent dans les fichiers .h car puisque mon coéquipier a utilisé QtCreator
//             pour faire le projet et moi VS, les fichiers ne sont pas bien répartis, ce qui, je pense , cause les warnings.

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
    explicit Roi(const Position& positionInitiale, const bool& estBlanc);
    ~Roi() override;

    std::vector<Position> deplacementsValides() const override;

private:
    static int nombreTotal_;
    static int nombreBlanc_;
    static int nombreNoir_;
};

}
