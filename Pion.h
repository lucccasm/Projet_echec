/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document est la description de la classe Pion, les mouvements de cette pi�ce ont �t� sp�cifi�s.
               De cette fa�on, le mouvement du pion est propre � lui-m�me et ne peut pas �tre confondu avec un autre type de pi�ce.
*/

// ATTENTION : Il semble que beaucoup de warnings apparaissent dans les fichiers .h car puisque mon co�quipier a utilis� QtCreator
//             pour faire le projet, les fichiers ne sont pas bien r�partis, ce qui, je pense , cause les warnings.
#pragma once
#include "Piece.h"

namespace model {

class Pion : public Piece {
public:
    Pion(const Position& positionInitiale, bool estBlanche);
    std::vector<Position> deplacementsValides() const override;

private:
    bool estBlanche;
};

}
