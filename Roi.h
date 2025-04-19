/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document est la description de la classe Roi, les mouvements de cette pi�ce ont �t� sp�cifi�s.
               De cette fa�on, le mouvement du roi est propre � lui-m�me et ne peut pas �tre confondu avec un autre type de pi�ce.
*/
// ATTENTION : Il semble que beaucoup de warnings apparaissent dans les fichiers .h car puisque mon co�quipier a utilis� QtCreator
//             pour faire le projet, les fichiers ne sont pas bien r�partis, ce qui, je pense , cause les warnings.
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
