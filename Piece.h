/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document est la description de la classe Pi�ce. La pi�ce a donc une position
                initiale et une position actuelle. La pi�ce est la classe m�re de toutes les pi�ces.
*/

// ATTENTION : Il semble que beaucoup de warnings apparaissent dans les fichiers .h car puisque mon co�quipier a utilis� QtCreator
//             pour faire le projet, les fichiers ne sont pas bien r�partis, ce qui, je pense , cause les warnings.


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
