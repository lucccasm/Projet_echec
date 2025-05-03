/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document décrit la classe DeplacementTemporaire, qui est utilisée pour déplacer temporairement une pièce sur l'échiquier.
              À l'aide du RAII, on l'utilise pour simuler un mouvement de pièce sans affecter la position réelle de la pièce, pour ensuite vérifier si
              le mouvement est valide.
*/


#pragma once
#include "Piece.h"

namespace model {

class DeplacementTemporaire {
public:
    DeplacementTemporaire(Piece& piece, const Position& positionTemporaire);
    ~DeplacementTemporaire();

private:
    Piece& pieceReference_;
    Position  positionOriginale_;
};

}
