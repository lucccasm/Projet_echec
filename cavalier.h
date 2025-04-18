/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document est la description de la classe Cavalier, les mouvements de cette pi�ce ont �t� sp�cifi�s.
               De cette fa�on, le mouvement du cavalier est propre � lui-m�me et ne peut pas �tre confondu avec un autre type de pi�ce.
               Malheureusement, il y a des warnings qui apparaissent pour tous le fichier .h de ce pion
*/
// ATTENTION : Il semble que beaucoup de warnings apparaissent dans les fichiers .h car puisque mon co�quipier a utilis� QtCreator
//             pour faire le projet, les fichiers ne sont pas bien r�partis, ce qui, je pense , cause les warnings.
#pragma once
#include "Piece.h"

namespace model {

class Cavalier : public Piece {
public:
    explicit Cavalier(const Position& positionInitiale);
    std::vector<Position> deplacementsValides() const override;
};

}
