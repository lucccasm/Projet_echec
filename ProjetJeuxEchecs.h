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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include "ModelJeuxEchecs.h"

namespace gui {
using model::Position;
class ProjetJeuxEchecs : public QMainWindow {
    Q_OBJECT

public:
    explicit ProjetJeuxEchecs(QWidget* parent=nullptr);
    ~ProjetJeuxEchecs() override = default;

private slots:
    void partieInitialisee();
    void pieceDeplacee(const Position& src, const Position& dest);
    void tourChangee(bool tourBlanc);
    void partieTermineeSignal();
    void caseCliquee(int idxCase);

private:
    void afficherPieces();
    void afficherTour();
    QString styleCase(int l,int c) const;
    static constexpr int TAILLE_ECHIQUIER=8;
    model::ModelJeuxEchecs modele_;
    std::vector<QPushButton*> boutonsCases;
    QLabel* etiquetteDuTour=nullptr;
    int indiceSelection=-1;
};
}
