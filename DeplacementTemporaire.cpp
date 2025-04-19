/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document décrit la classe DeplacementTemporaire, qui est utilisée pour déplacer temporairement une pièce sur l'échiquier.
			  À l'aide du RAII, on l'utilise pour simuler un mouvement de pièce sans affecter la position réelle de la pièce, pour ensuite vérifier si 
              le mouvement est valide.
*/

#include "DeplacementTemporaire.h"

namespace model {

DeplacementTemporaire::DeplacementTemporaire(Piece& piece, const Position& positionTemporaire )
    : pieceReference(piece), positionOriginale(piece.obtenirPosition())
{
    pieceReference.definirPosition(positionTemporaire);
}

DeplacementTemporaire::~DeplacementTemporaire()
{
    pieceReference.definirPosition(positionOriginale);
}

}
