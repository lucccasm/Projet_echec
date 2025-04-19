/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document est la description de la classe Tour, les mouvements de cette pièce ont été spécifiés.
               De cette façon, le mouvement de la tour est propre à lui-même et ne peut pas être confondu avec un autre type de pièce.
*/
// ATTENTION : Il semble que beaucoup de warnings apparaissent dans les fichiers .h car puisque mon coéquipier a utilisé QtCreator
//             pour faire le projet, les fichiers ne sont pas bien répartis, ce qui, je pense , cause les warnings.
#pragma once
#include "Piece.h"

namespace model {

class Tour : public Piece {
public:
    explicit Tour(const Position& positionInitiale);
    std::vector<Position> deplacementsValides() const override;
};

}

