/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document d�crit la classe DeplacementTemporaire, qui est utilis�e pour d�placer temporairement une pi�ce sur l'�chiquier.
			  � l'aide du RAII, on l'utilise pour simuler un mouvement de pi�ce sans affecter la position r�elle de la pi�ce, pour ensuite v�rifier si 
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
