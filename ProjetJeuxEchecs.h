/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document est le coeur du projet, il contient la classe ProjetJeuxEchecs qui est la classe principale de l'application.
              Cette classe gère l'interface graphique et la logique du jeu d'échecs. Avec ce fichier, il est possible d'avoir une multitude
              de fonctionnalités, ça permet de savoir si c'est le tour du joueur blanc ou noir, de savoir si une pièce est bloquée,
              de savoir si une case est cliquée.
*/

#pragma once
#include <QtWidgets/QMainWindow>
#include <vector>
#include <memory>
#include "Piece.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>

namespace gui {

class ProjetJeuxEchecs : public QMainWindow {
    Q_OBJECT

public:
    explicit ProjetJeuxEchecs(QWidget* parent = nullptr);
    ~ProjetJeuxEchecs() override;

private slots:
    void caseCliquee(int indiceCase);

private:
    void initialiserPieces();
    void afficherPieces();
    void afficherTour();
    QString styleCase(int ligne, int colonne) const;

    int  obtenirIndice(const model::Position& position) const;
    bool estBloque(const model::Position& source, const model::Position& destination) const;
    bool estBlanc(size_t indicePiece) const { return estBlancV[indicePiece]; }

    static constexpr int TAILLE_ECHIQUIER = 8;

    std::vector<std::unique_ptr<model::Piece>> pieces;
    std::vector<bool> estBlancV;
    std::vector<QPushButton*> boutonsCases;
    QLabel* etiquetteDuTour = nullptr;

    int indiceSelection = -1;
    bool tourBlanc = true;
    bool partieEstTerminee = false;
};

}
