/*
Projet final

Noms: Lucas Montpetit, Jacob Desaulniers

Description : Ce document est le coeur du projet, il contient la classe ProjetJeuxEchecs qui est la classe principale de l'application.
			  Cette classe gère l'interface graphique et la logique du jeu d'échecs. Avec ce fichier, il est possible d'avoir une multitude
			  de fonctionnalités, ça permet de savoir si c'est le tour du joueur blanc ou noir, de savoir si une pièce est bloquée, 
              de savoir si une case est cliquée.
*/

#include "ProjetJeuxEchecs.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMessageBox>
#include <algorithm>
#include "Roi.h"
#include "Dame.h"
#include "Tour.h"
#include "Fou.h"
#include "Cavalier.h"
#include "Pion.h"

namespace gui {
using model::Position;

int ProjetJeuxEchecs::obtenirIndice(const Position& position) const {
    for (size_t i = 0; i < pieces.size(); ++i) {
        if (pieces[i]->obtenirPosition() == position) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

bool ProjetJeuxEchecs::estBloque(const Position& source, const Position& destination) const {
    int deltaLigne = (destination.first > source.first) ? 1 :
                         (destination.first < source.first) ? -1 : 0;
    int deltaCol   = (destination.second > source.second) ? 1 :
                       (destination.second < source.second) ? -1 : 0;
    Position curseur = source;
    while (curseur != destination) {
        curseur.first  += deltaLigne;
        curseur.second += deltaCol;
        if (curseur != destination && obtenirIndice(curseur) != -1) {
            return true;
        }
    }
    return false;
}

ProjetJeuxEchecs::ProjetJeuxEchecs(QWidget* parent) : QMainWindow(parent) {
    auto* central = new QWidget(this);
    setCentralWidget(central);
    auto* layout = new QHBoxLayout(central);
    auto* grille = new QGridLayout();
    grille->setSpacing(0);
    for (int ligne = 0; ligne < TAILLE_ECHIQUIER; ++ligne) {
        for (int colonne = 0; colonne < TAILLE_ECHIQUIER; ++colonne) {
            auto* btn = new QPushButton(this);
            btn->setFixedSize(60, 60);
            btn->setStyleSheet(styleCase(ligne, colonne));
            grille->addWidget(btn, ligne, colonne);
            int idx = ligne * TAILLE_ECHIQUIER + colonne;
            boutonsCases.push_back(btn);
            connect(btn, &QPushButton::clicked, this, [this, idx](){ caseCliquee(idx); });
        }
    }
    layout->addLayout(grille);
    auto* menu = new QVBoxLayout();
    etiquetteDuTour = new QLabel(this);
    etiquetteDuTour->setAlignment(Qt::AlignCenter);
    menu->addWidget(etiquetteDuTour);
    auto* btnNew = new QPushButton("Nouvelle Partie", this);
    auto* btnQuit = new QPushButton("Quitter", this);
    menu->addWidget(btnNew);
    menu->addWidget(btnQuit);
    menu->addStretch();
    layout->addLayout(menu);
    connect(btnNew, &QPushButton::clicked, this, [this](){
        tourBlanc = true;
        partieEstTerminee = false;
        indiceSelection = -1;
        initialiserPieces();
        afficherPieces();
        afficherTour();
    });
    connect(btnQuit, &QPushButton::clicked, this, &QMainWindow::close);
    initialiserPieces();
    afficherPieces();
    afficherTour();
}

ProjetJeuxEchecs::~ProjetJeuxEchecs() = default;

QString ProjetJeuxEchecs::styleCase(int ligne, int colonne) const {
    bool claire = ((ligne + colonne) % 2 == 0);
    return claire ? "background-color:#EEE;" : "background-color:#555;";
}

void ProjetJeuxEchecs::afficherTour() {
    etiquetteDuTour->setText(QString("C'est le tour du joueur %1").arg(tourBlanc ? "Blanc" : "Noir"));
}

void ProjetJeuxEchecs::initialiserPieces() {
    pieces.clear();
    estBlancV.clear();

    pieces.emplace_back(std::make_unique<model::Tour>(Position{0,0}));
    estBlancV.push_back(true);
    pieces.emplace_back(std::make_unique<model::Cavalier>(Position{0,1}));
    estBlancV.push_back(true);
    pieces.emplace_back(std::make_unique<model::Fou>(Position{0,2}));
    estBlancV.push_back(true);
    pieces.emplace_back(std::make_unique<model::Dame>(Position{0,3}));
    estBlancV.push_back(true);
    pieces.emplace_back(std::make_unique<model::Roi>(Position{0,4}));
    estBlancV.push_back(true);
    pieces.emplace_back(std::make_unique<model::Fou>(Position{0,5}));
    estBlancV.push_back(true);
    pieces.emplace_back(std::make_unique<model::Cavalier>(Position{0,6}));
    estBlancV.push_back(true);
    pieces.emplace_back(std::make_unique<model::Tour>(Position{0,7}));
    estBlancV.push_back(true);
    for (int i = 0; i < 8; ++i) {
        pieces.emplace_back(
            std::make_unique<model::Pion>(Position{1,i}, true)
            );
        estBlancV.push_back(true);
    }

    pieces.emplace_back(std::make_unique<model::Tour>(Position{7,0}));
    estBlancV.push_back(false);
    pieces.emplace_back(std::make_unique<model::Cavalier>(Position{7,1}));
    estBlancV.push_back(false);
    pieces.emplace_back(std::make_unique<model::Fou>(Position{7,2}));
    estBlancV.push_back(false);
    pieces.emplace_back(std::make_unique<model::Dame>(Position{7,3}));
    estBlancV.push_back(false);
    pieces.emplace_back(std::make_unique<model::Roi>(Position{7,4}));
    estBlancV.push_back(false);
    pieces.emplace_back(std::make_unique<model::Fou>(Position{7,5}));
    estBlancV.push_back(false);
    pieces.emplace_back(std::make_unique<model::Cavalier>(Position{7,6}));
    estBlancV.push_back(false);
    pieces.emplace_back(std::make_unique<model::Tour>(Position{7,7}));
    estBlancV.push_back(false);
    for (int i = 0; i < 8; ++i) {
        pieces.emplace_back(
            std::make_unique<model::Pion>(Position{6,i}, false)
            );
        estBlancV.push_back(false);
    }
}

void ProjetJeuxEchecs::afficherPieces() {
    for (int i = 0; i < TAILLE_ECHIQUIER * TAILLE_ECHIQUIER; ++i) {
        int ligne = i / TAILLE_ECHIQUIER;
        int colonne = i % TAILLE_ECHIQUIER;
        boutonsCases[i]->setText("");
        boutonsCases[i]->setStyleSheet(styleCase(ligne,colonne));
    }
    for (size_t i = 0; i < pieces.size(); ++i) {
        auto [ligne,colonne] = pieces[i]->obtenirPosition();
        auto* btn = boutonsCases[ligne * TAILLE_ECHIQUIER + colonne];
        char L='?';
        if (dynamic_cast<model::Tour*>(pieces[i].get()))          L='T';
        else if (dynamic_cast<model::Cavalier*>(pieces[i].get())) L='C';
        else if (dynamic_cast<model::Fou*>(pieces[i].get()))      L='F';
        else if (dynamic_cast<model::Dame*>(pieces[i].get()))     L='D';
        else if (dynamic_cast<model::Roi*>(pieces[i].get()))      L='R';
        else if (dynamic_cast<model::Pion*>(pieces[i].get()))     L='P';
        QString col = estBlancV[i] ? "white" : "black";
        btn->setText(QString(L));
        btn->setStyleSheet(styleCase(ligne,colonne) + QString("font-size:20px; color:%1;").arg(col));
    }
}

void ProjetJeuxEchecs::caseCliquee(int indiceCase) {
    if (partieEstTerminee) return;
    int ligne = indiceCase / TAILLE_ECHIQUIER;
    int colonne = indiceCase % TAILLE_ECHIQUIER;
    Position clic{ligne,colonne};
    if (indiceSelection < 0) {
        int idx = obtenirIndice(clic);
        if (idx < 0) return;
        if (estBlanc(idx) != tourBlanc) {
            QMessageBox::warning(this,"Tour","Ce n'est pas votre tour !"); return;
        }
        auto brut = pieces[idx]->deplacementsValides();
        std::vector<Position> filt;
        for (auto& p : brut) {
            int occ = obtenirIndice(p);
            if (occ!=-1 && estBlanc(occ)==estBlanc(idx)) continue;
            bool gl = dynamic_cast<model::Tour*>(pieces[idx].get())||dynamic_cast<model::Fou*>(pieces[idx].get())||dynamic_cast<model::Dame*>(pieces[idx].get());
            if (gl && estBloque(clic,p)) continue;
            filt.push_back(p);
        }
        if (filt.empty()) {
            QMessageBox::warning(this,"Bloqué","Cette pièce ne peut pas bouger."); return;
        }
        afficherPieces(); afficherTour();
        indiceSelection = indiceCase;
        boutonsCases[indiceCase]->setStyleSheet(boutonsCases[indiceCase]->styleSheet()+"border:2px solid red;");
        for (auto& p : filt) {
            int id=p.first*TAILLE_ECHIQUIER+p.second; boutonsCases[id]->setStyleSheet(boutonsCases[id]->styleSheet()+"border:2px solid green;");
        }
    }
    else {
        Position src{indiceSelection/TAILLE_ECHIQUIER,indiceSelection%TAILLE_ECHIQUIER};
        int idx=obtenirIndice(src);
        auto brut = pieces[idx]->deplacementsValides();
        std::vector<Position> filt;
        for (auto& p: brut) {
            int occ=obtenirIndice(p);
            if (occ!=-1 && estBlanc(occ)==estBlanc(idx)) continue;
            bool gl = dynamic_cast<model::Tour*>(pieces[idx].get())||dynamic_cast<model::Fou*>(pieces[idx].get())||dynamic_cast<model::Dame*>(pieces[idx].get());
            if (gl && estBloque(src,p)) continue;
            filt.push_back(p);
        }
        boutonsCases[indiceSelection]->setStyleSheet(styleCase(src.first,src.second));
        if (std::find(filt.begin(),filt.end(),clic)==filt.end()) {
            QMessageBox::warning(this,"Mouvement","Non valide"); indiceSelection=-1; return;
        }
        int occ = obtenirIndice(clic);
        if (occ !=- 1 && dynamic_cast<model::Roi*>(pieces[occ].get())) {
            QMessageBox::information(this,"Fin","Roi capturé."); partieEstTerminee=true; }
        if (occ!=-1) { pieces.erase(pieces.begin()+occ); estBlancV.erase(estBlancV.begin()+occ); if (occ<idx) --idx;
        }
        pieces[idx]->definirPosition(clic);
        tourBlanc =! tourBlanc;
        afficherPieces(); afficherTour(); indiceSelection =- 1;
    }
}

}
