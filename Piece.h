/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document est la description de la classe Pièce. La pièce a donc une position
                initiale et une position actuelle. La pièce est la classe mère de toutes les pièces.
*/

// ATTENTION : Il semble que beaucoup de warnings apparaissent dans les fichiers .h car puisque mon coéquipier a utilisé QtCreator
//             pour faire le projet, les fichiers ne sont pas bien répartis, ce qui, je pense , cause les warnings.


#pragma once
#include <vector>
#include <utility>

namespace model {
using Position = std::pair<int, int>;

class Piece {
public:
    explicit Piece(const Position& positionInitiale);
    virtual ~Piece();

    virtual std::vector<Position> deplacementsValides() const = 0;
    const Position& obtenirPosition() const;
    void definirPosition(const Position& nouvellePosition);

protected:
    Position positionActuelle;
};
}
