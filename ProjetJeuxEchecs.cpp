/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document est le coeur du projet, il contient la classe ProjetJeuxEchecs qui est la classe principale de l'application.
              Cette classe gère l'interface graphique et la logique du jeu d'échecs. Avec ce fichier, il est possible d'avoir une multitude
              de fonctionnalités, ça permet de savoir si c'est le tour du joueur blanc ou noir, de savoir si une pièce est bloquée,
              de savoir si une case est cliquée.
*/

#include "ProjetJeuxEchecs.h"
#include "Tour.h"
#include "Cavalier.h"
#include "Fou.h"
#include "Dame.h"
#include "Roi.h"
#include "Pion.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMessageBox>
#include <QInputDialog>

namespace gui {

using model::Position;
using model::StatutMouvement;

ProjetJeuxEchecs::ProjetJeuxEchecs(QWidget* parent): QMainWindow(parent), modele_()
{
    auto* central=new QWidget(this);
    setCentralWidget(central);
    auto* layout=new QHBoxLayout(central);
    auto* grille=new QGridLayout(); grille->setSpacing(0);
    for(int l = 0; l < TAILLE_ECHIQUIER; ++l) {
        for(int c = 0; c < TAILLE_ECHIQUIER; ++c) {
            auto* btn=new QPushButton(this);
            btn->setFixedSize(60,60);
            btn->setStyleSheet(styleCase(l, c));
            grille->addWidget(btn, l, c);
            int idx = l * TAILLE_ECHIQUIER + c; boutonsCases.push_back(btn);
            connect(btn,&QPushButton::clicked, this, [this, idx]() { caseCliquee(idx); });
        }
    }

    layout->addLayout(grille);
    auto* menu = new QVBoxLayout();
    etiquetteDuTour = new QLabel(this);
    etiquetteDuTour->setAlignment(Qt::AlignCenter);
    menu->addWidget(etiquetteDuTour);
    auto* btnNew = new QPushButton("Nouvelle Partie",this);
    auto* btnQuit = new QPushButton("Quitter",this);
    menu->addWidget(btnNew); menu->addWidget(btnQuit); menu->addStretch();
    layout->addLayout(menu);

    connect(btnNew, &QPushButton::clicked, this, &ProjetJeuxEchecs::nouveauJeuClic);
    connect(btnQuit, &QPushButton::clicked, this, &QMainWindow::close);

    connect(&modele_, &model::ModelJeuxEchecs::erreurRoi,
            this, [this](const QString& msg){
                QMessageBox::warning(this, "Erreur création Roi", msg);
            });

    connect(&modele_, &model::ModelJeuxEchecs::partieInitialisee,
            this, &ProjetJeuxEchecs::partieInitialisee);
    connect(&modele_, &model::ModelJeuxEchecs::pieceDeplacee,
            this, &ProjetJeuxEchecs::pieceDeplacee);
    connect(&modele_, &model::ModelJeuxEchecs::tourChangee,
            this, &ProjetJeuxEchecs::tourChangee);
    connect(&modele_, &model::ModelJeuxEchecs::partieTermineeSignal,
            this, &ProjetJeuxEchecs::partieTermineeSignal);

    connect(&modele_, &model::ModelJeuxEchecs::roiEnEchec,
            this, [this](bool roiBlanc){
                QString msg = roiBlanc
                                  ? "Vous mettez le roi blanc en échec"
                                  : "Vous mettez le roi noir en échec";
                QMessageBox::information(this, "Échec", msg);
            });
    connect(&modele_, &model::ModelJeuxEchecs::roiEnEchecEtMat,
            this, [this](bool roiBlanc){
                QString msg = roiBlanc
                                  ? "Échec et mat sur le roi blanc"
                                  : "Échec et mat sur le roi noir";
                QMessageBox::information(this, "Échec et mat", msg);
            });

    nouveauJeuClic();
}

void ProjetJeuxEchecs::nouveauJeuClic() {
    QStringList modes;
    modes << "Standard" << "Rapide";
    bool ok;
    QString choix = QInputDialog::getItem(this, tr("Nouveau jeu"), tr("Mode de jeu:"), modes, 0, false, &ok);
    if (!ok) return;

    if (choix == "Standard") {
        modele_.nouvellePartie();
    } else {
        modele_.nouvellePartieRapide();
    }

    indiceSelection = -1;
    afficherPieces();
    afficherTour();
}

void ProjetJeuxEchecs::partieInitialisee()
{
    afficherPieces();
    afficherTour();
}

void ProjetJeuxEchecs::pieceDeplacee(const Position&, const Position&)
{
    afficherPieces();
}

void ProjetJeuxEchecs::tourChangee(bool)
{
    afficherTour();
}

void ProjetJeuxEchecs::partieTermineeSignal()
{
    QMessageBox::information(this, "Fin de partie", "Le roi a été capturé");
}

QString ProjetJeuxEchecs::styleCase(int l,int c) const
{
    return ((l+c)%2==0)?"background-color:#F0D9B5;":"background-color:#B58863;";
}

void ProjetJeuxEchecs::afficherTour()
{
    etiquetteDuTour->setText(
        QString("C'est le tour du joueur %1").arg(modele_.tourBlanc()?"Blanc":"Noir")
        );
}

void ProjetJeuxEchecs::afficherPieces()
{
    for(int i = 0; i < TAILLE_ECHIQUIER * TAILLE_ECHIQUIER; ++i) {
        int l = i / TAILLE_ECHIQUIER, c = i % TAILLE_ECHIQUIER;
        boutonsCases[i]->setText(""); boutonsCases[i]->setStyleSheet(styleCase(l, c));
    }

    for(size_t i = 0; i < modele_.nombrePieces(); ++i){
        auto pos = modele_.piece(i).obtenirPosition();
        int l = pos.first, c = pos.second;
        auto* btn = boutonsCases[l * TAILLE_ECHIQUIER + c];
        char L = '?';
        if(dynamic_cast<const model::Tour*>(&modele_.piece(i))) L = 'T';
        else if(dynamic_cast<const model::Cavalier*>(&modele_.piece(i))) L = 'C';
        else if(dynamic_cast<const model::Fou*>(&modele_.piece(i))) L = 'F';
        else if(dynamic_cast<const model::Dame*>(&modele_.piece(i))) L = 'D';
        else if(dynamic_cast<const model::Roi*>(&modele_.piece(i))) L = 'R';
        else if(dynamic_cast<const model::Pion*>(&modele_.piece(i))) L = 'P';
        QString col = modele_.estBlanc(i) ? "#FFFFFF" : "#000000";
        btn->setText(QString(L));
        btn->setStyleSheet(styleCase(l, c) + QString("font-size:20px; color:%1;").arg(col));
    }
}

void ProjetJeuxEchecs::caseCliquee(int idxCase)
{
    if (modele_.partieTerminee())
        return;

    afficherPieces();
    afficherTour();

    constexpr int N = TAILLE_ECHIQUIER;
    Position clic{ idxCase / N, idxCase % N };

    if (indiceSelection == idxCase) {
        indiceSelection = -1;
        return;
    }

    if (indiceSelection < 0) {
        auto opt = modele_.obtenirIndice(clic);
        if (!opt) return;

        size_t idxPièce = *opt;
        if (modele_.estBlanc(idxPièce) != modele_.tourBlanc()) {
            QMessageBox::warning(this, "Tour", "Ce n'est pas votre tour.");
            return;
        }

        auto coups = modele_.deplacementsLegaux(clic);
        if (coups.empty()) {
            QMessageBox::warning(this, "Bloqué",
                                 "Cette pièce ne peut pas bouger.");
            return;
        }

        indiceSelection = idxCase;
        boutonsCases[idxCase]->setStyleSheet(
            boutonsCases[idxCase]->styleSheet()
            + "border:2px solid blue;"
            );

        for (auto& p : coups) {
            int id = p.first * N + p.second;
            boutonsCases[id]->setStyleSheet(
                boutonsCases[id]->styleSheet()
                + "border:2px solid green;"
                );
        }
    }
    else {
        Position src{
            indiceSelection / N,
            indiceSelection % N
        };

        auto coups = modele_.deplacementsLegaux(src);
        bool estLegal = std::find(coups.begin(), coups.end(), clic)
                        != coups.end();

        if (estLegal) {
            if (modele_.metEnEchecPropreRoi(src, clic)) {
                QMessageBox::warning(this, "Échec", "Ce mouvement met votre roi en échec.");
            } else {
                modele_.deplacer(src, clic);
            }
        }
        else {
            QMessageBox::warning(this, "Impossible",
                                 "Ce déplacement n'est pas autorisé.");
        }

        afficherPieces();
        afficherTour();
        indiceSelection = -1;
    }
}

}
