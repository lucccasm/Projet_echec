/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document est la description de la classe Cavalier, les mouvements de cette pièce ont été spécifiés.
               De cette façon, le mouvement du cavalier est propre à lui-même et ne peut pas être confondu avec un autre type de pièce.
               Malheureusement, il y a des warnings qui apparaissent pour tous le fichier .h de ce pion
*/
// ATTENTION : Il semble que beaucoup de warnings apparaissent dans les fichiers .h car puisque mon coéquipier a utilisé QtCreator
//             pour faire le projet et moi VS, les fichiers ne sont pas bien répartis, ce qui, je pense , cause les warnings.

#pragma once
#include "Piece.h"

namespace model {

class Cavalier : public Piece {
public:
    explicit Cavalier(const Position& positionInitiale, const bool& estBlanc);
    std::vector<Position> deplacementsValides() const override;
};

}
