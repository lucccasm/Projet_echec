#include "ProjetJeuxEchecs.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <algorithm>                         // Pour std::find
#include "Roi.h"
#include "DeplacementTemporaire.h"

namespace gui {

using model::Position;

ProjetJeuxEchecs::ProjetJeuxEchecs(QWidget* parent)
    : QMainWindow(parent)
{
    QWidget* zoneCentrale = new QWidget(this);
    setCentralWidget(zoneCentrale);

    QHBoxLayout* dispositionPrincipale = new QHBoxLayout(zoneCentrale);
    dispositionPrincipale->setContentsMargins(10,10,10,10);
    dispositionPrincipale->setSpacing(20);

    QGridLayout* dispositionGrille = new QGridLayout();
    dispositionGrille->setSpacing(0);

    for (int ligne = 0; ligne < dimension; ++ligne) {
        for (int colonne = 0; colonne < dimension; ++colonne) {
            QPushButton* bouton = new QPushButton(this);
            bouton->setFixedSize(60,60);
            bouton->setStyleSheet(styleCase(ligne,colonne));
            dispositionGrille->addWidget(bouton, ligne, colonne);

            int indice = ligne * dimension + colonne;
            boutons.push_back(bouton);
            connect(bouton, &QPushButton::clicked,
                    this, [this,indice](){ caseCliquee(indice); });
        }
    }
    dispositionPrincipale->addLayout(dispositionGrille);

    QVBoxLayout* dispositionMenu = new QVBoxLayout();
    QLabel* etiquetteMenu = new QLabel("Menu", this);
    etiquetteMenu->setStyleSheet("font-weight:bold; font-size:18px;");
    dispositionMenu->addWidget(etiquetteMenu);

    QPushButton* boutonNouvelle = new QPushButton("Nouvelle Partie", this);
    QPushButton* boutonQuitter = new QPushButton("Quitter", this);
    dispositionMenu->addWidget(boutonNouvelle);
    dispositionMenu->addWidget(boutonQuitter);
    dispositionMenu->addStretch();
    dispositionPrincipale->addLayout(dispositionMenu);

    connect(boutonNouvelle, &QPushButton::clicked, this, [this](){
        tourBlanc = true;
        partieTerminee = false;
        indiceSelection = -1;
        initialiserPieces(); afficherPieces();
    });
    connect(boutonQuitter, &QPushButton::clicked, this, &QMainWindow::close);

    initialiserPieces();
    afficherPieces();
}

ProjetJeuxEchecs::~ProjetJeuxEchecs() = default;

QString ProjetJeuxEchecs::styleCase(int ligne, int colonne) const {
    bool caseClaire = ((ligne+colonne)%2==0);
    return caseClaire ? "background-color:#EEE;" : "background-color:#555;";
}

void ProjetJeuxEchecs::initialiserPieces() {
    piecesEchecs.clear();
    piecesEchecs.emplace_back(std::make_unique<model::Roi>(Position{0,4})); // roi blanc
    piecesEchecs.emplace_back(std::make_unique<model::Roi>(Position{7,4})); // roi noir
}

void ProjetJeuxEchecs::afficherPieces() {
    for (int i=0; i<dimension*dimension; ++i) {
        int ligne = i/dimension;
        int colonne = i%dimension;
        boutons[i]->setText("");
        boutons[i]->setStyleSheet(styleCase(ligne,colonne));
    }
    for (size_t i=0; i<piecesEchecs.size(); ++i) {
        auto [ligne,colonne] = piecesEchecs[i]->getPosition();
        QPushButton* bouton = boutons[ligne*dimension + colonne];
        if (i==0) {
            bouton->setText("♔");
            bouton->setStyleSheet(styleCase(ligne,colonne)+"color:black;font-size:24px;");
        } else {
            bouton->setText("♚");
            bouton->setStyleSheet(styleCase(ligne,colonne)+"color:white;font-size:24px;");
        }
    }
}

void ProjetJeuxEchecs::caseCliquee(int indice) {
    if (partieTerminee) return;
    int ligne = indice/dimension;
    int colonne = indice%dimension;
    if (indiceSelection < 0) {
        // Sélection de la pièce du bon joueur
        for (size_t i=0; i<piecesEchecs.size(); ++i) {
            auto [lr,lc] = piecesEchecs[i]->getPosition();
            if (lr==ligne && lc==colonne) {
                if ((tourBlanc && i==0) || (!tourBlanc && i==1)) {
                    indiceSelection = indice;
                    boutons[indiceSelection]->setStyleSheet(
                        boutons[indiceSelection]->styleSheet()+"border:2px solid red;");
                }
                return;
            }
        }
    } else {
        Position source{indiceSelection/dimension, indiceSelection%dimension};
        size_t indiceJoueur = tourBlanc ? 0 : 1;
        auto deplacementsPossibles = piecesEchecs[indiceJoueur]->deplacementsValides();
        Position destination{ligne,colonne};
        boutons[indiceSelection]->setStyleSheet(
            styleCase(source.first, source.second));
        if (std::find(deplacementsPossibles.begin(),
                      deplacementsPossibles.end(), destination)
            == deplacementsPossibles.end()) {
            QMessageBox::warning(this,"Mouvement","Mouvement non valide pour le roi");
        } else {
            size_t indiceAdversaire = (indiceJoueur==0?1:0);
            if (piecesEchecs[indiceAdversaire]->getPosition() == destination) {
                QMessageBox::information(this,"Fin de partie",
                                         QString("Le joueur %1 a capturé le roi. Fin du jeu.")
                                             .arg(tourBlanc?"Blanc":"Noir"));
                partieTerminee = true;
            }
            piecesEchecs[indiceJoueur]->setPosition(destination);
            afficherPieces();
            tourBlanc = !tourBlanc;
        }
        indiceSelection = -1;
    }
}

} // namespace gui
