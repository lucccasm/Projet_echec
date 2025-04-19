/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document est la description de la classe Fou, les mouvements de cette pi�ce ont �t� sp�cifi�s.
               De cette fa�on, le mouvement du fou est propre � lui-m�me et ne peut pas �tre confondu avec un autre type de pi�ce.
*/

// ATTENTION : Il semble que beaucoup de warnings apparaissent dans les fichiers .h car puisque mon co�quipier a utilis� QtCreator
//             pour faire le projet, les fichiers ne sont pas bien r�partis, ce qui, je pense , cause les warnings.
#pragma once
#include "Piece.h"

namespace model {

class Fou : public Piece {
public:
    explicit Fou(const Position& positionInitiale);
    std::vector<Position> deplacementsValides() const override;
};

}

