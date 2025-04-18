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

int ProjetJeuxEchecs::indexPieceEn(Position pos) const {
    for(size_t i = 0; i < pieces.size(); ++i)
        if(pieces[i]->getPosition() == pos) return int(i);
    return -1;
}
bool ProjetJeuxEchecs::estBloqueEntre(Position src, Position dest) const {
    int dr = (dest.first > src.first) ? 1 : (dest.first<src.first) ? - 1 : 0;
    int dc = (dest.second > src.second) ? 1 : (dest.second < src.second) ? - 1 : 0;
    Position cur = src;
    while(cur != dest) {
        cur.first += dr;
        cur.second += dc;
        if (cur != dest && indexPieceEn(cur) != -1) return true;
    }
    return false;
}

ProjetJeuxEchecs::ProjetJeuxEchecs(QWidget* parent)
    : QMainWindow(parent)
{
    auto* central = new QWidget(this);
    setCentralWidget(central);
    auto* layout = new QHBoxLayout(central);
    auto* grille = new QGridLayout();
    grille->setSpacing(0);
    for(int r = 0; r < dimension; ++r) for (int c = 0; c < dimension; ++c) {
            auto* btn = new QPushButton(this);
            btn->setFixedSize(60, 60);
            btn->setStyleSheet(styleCase(r, c));
            grille->addWidget(btn, r, c);
            int idx = r * dimension + c; boutons.push_back(btn);
            connect(btn, &QPushButton::clicked, this, [this, idx]{caseCliquee(idx);});
        }
    layout->addLayout(grille);
    auto* menu = new QVBoxLayout();
    etiquetteTour = new QLabel(this); etiquetteTour->setAlignment(Qt::AlignCenter);
    menu-> addWidget(etiquetteTour);
    QPushButton* newG = new QPushButton("Nouvelle Partie", this);
    QPushButton* quit = new QPushButton("Quitter", this);
    menu->addWidget(newG);
    menu->addWidget(quit);
    menu->addStretch();
    layout->addLayout(menu);
    connect(newG, &QPushButton::clicked, this, [this]{
        tourBlanc = true;
        partieTerminee = false;
        idxSelection=-1;
        initialiserPieces();
        afficherPieces();
        afficherTour();
    });
    connect(quit, &QPushButton::clicked, this, &QMainWindow::close);
    initialiserPieces();
    afficherPieces();
    afficherTour();
}

ProjetJeuxEchecs::~ProjetJeuxEchecs() = default;

QString ProjetJeuxEchecs::styleCase(int l,int c) const {
    return ((l + c) % 2 == 0) ? "background-color:#EEE;":"background-color:#555;";
}

void ProjetJeuxEchecs::afficherTour() {
    etiquetteTour->setText(
        QString("C'est le tour du joueur %1").arg(tourBlanc?"Blanc":"Noir")
        );
}

void ProjetJeuxEchecs::initialiserPieces() {
    pieces.clear(); estBlancVecteur.clear();

    pieces.emplace_back(std::make_unique<model::Tour>(Position{0, 0})); estBlancVecteur.push_back(true);
    pieces.emplace_back(std::make_unique<model::Cavalier>(Position{0, 1})); estBlancVecteur.push_back(true);
    pieces.emplace_back(std::make_unique<model::Fou>(Position{0, 2})); estBlancVecteur.push_back(true);
    pieces.emplace_back(std::make_unique<model::Dame>(Position{0, 3})); estBlancVecteur.push_back(true);
    pieces.emplace_back(std::make_unique<model::Roi>(Position{0, 4})); estBlancVecteur.push_back(true);
    pieces.emplace_back(std::make_unique<model::Fou>(Position{0, 5})); estBlancVecteur.push_back(true);
    pieces.emplace_back(std::make_unique<model::Cavalier>(Position{0, 6})); estBlancVecteur.push_back(true);
    pieces.emplace_back(std::make_unique<model::Tour>(Position{0, 7})); estBlancVecteur.push_back(true);
    for (int i = 0; i < 8; ++i) {
        pieces.emplace_back(std::make_unique<model::Pion>(Position{1, i},true));
        estBlancVecteur.push_back(true);
    }

    pieces.emplace_back(std::make_unique<model::Tour>(Position{7, 0})); estBlancVecteur.push_back(false);
    pieces.emplace_back(std::make_unique<model::Cavalier>(Position{7, 1})); estBlancVecteur.push_back(false);
    pieces.emplace_back(std::make_unique<model::Fou>(Position{7, 2})); estBlancVecteur.push_back(false);
    pieces.emplace_back(std::make_unique<model::Dame>(Position{7, 3})); estBlancVecteur.push_back(false);
    pieces.emplace_back(std::make_unique<model::Roi>(Position{7, 4})); estBlancVecteur.push_back(false);
    pieces.emplace_back(std::make_unique<model::Fou>(Position{7, 5})); estBlancVecteur.push_back(false);
    pieces.emplace_back(std::make_unique<model::Cavalier>(Position{7, 6})); estBlancVecteur.push_back(false);
    pieces.emplace_back(std::make_unique<model::Tour>(Position{7, 7})); estBlancVecteur.push_back(false);
    for(int i = 0; i < 8; ++i) {
        pieces.emplace_back(std::make_unique<model::Pion>(Position{6, i},false));
        estBlancVecteur.push_back(false);
    }
}

void ProjetJeuxEchecs::afficherPieces() {

    for(int i = 0; i < dimension * dimension; ++i){
        int r = i / dimension, c = i % dimension;
        boutons[i]->setText(""); boutons[i]->setStyleSheet(styleCase(r, c));
    }

    for(size_t i = 0; i < pieces.size(); ++i){
        auto [r, c] = pieces[i]->getPosition();
        QPushButton* b = boutons[r * dimension + c];
        char L = '?';
        if (dynamic_cast<model::Tour*>(pieces[i].get()))          L='T';
        else if (dynamic_cast<model::Cavalier*>(pieces[i].get())) L='C';
        else if (dynamic_cast<model::Fou*>(pieces[i].get()))      L='F';
        else if (dynamic_cast<model::Dame*>(pieces[i].get()))     L='D';
        else if (dynamic_cast<model::Roi*>(pieces[i].get()))      L='R';
        else if (dynamic_cast<model::Pion*>(pieces[i].get()))     L='P';
        QString col = estBlancVecteur[i]?"white":"black";
        b->setText(QString(L));
        b->setStyleSheet(styleCase(r, c) + QString("font-size:20px; color:%1;").arg(col));
    }
}

void ProjetJeuxEchecs::caseCliquee(int idx) {
    if(partieTerminee) return;
    int r = idx / dimension, c = idx % dimension;
    Position clic{r, c};
    if (idxSelection < 0){
        int pieceIdx = indexPieceEn(clic);
        if (pieceIdx < 0) return;
        if (estBlanc(pieceIdx) != tourBlanc){
            QMessageBox::warning(this,"Tour","Ce n'est pas votre tour !");
            return;
        }

        auto mouvementsInitiaux = pieces[pieceIdx]->deplacementsValides();
        std::vector<Position> mouvements;
        for (auto& m : mouvementsInitiaux) {
            int occ = indexPieceEn(m);
            if (occ != -1 && estBlanc(occ)==estBlanc(pieceIdx)) continue;
            bool glisse = dynamic_cast<model::Tour*>(pieces[pieceIdx].get())
                          || dynamic_cast<model::Fou*>(pieces[pieceIdx].get())
                          || dynamic_cast<model::Dame*>(pieces[pieceIdx].get());
            if (glisse && estBloqueEntre(clic,m)) continue;
            mouvements.push_back(m);
        }
        if (mouvements.empty()){
            QMessageBox::warning(this,"Bloqué","Cette pièce ne peut pas bouger.");
            return;
        }

        afficherPieces(); afficherTour();
        idxSelection=idx;
        boutons[idx]->setStyleSheet(boutons[idx]->styleSheet()+"border:2px solid red;");
        for(auto& m:mouvements){int id=m.first*dimension+m.second;
            boutons[id]->setStyleSheet(boutons[id]->styleSheet()+"border:2px solid green;");
        }

    }
    else {
        Position src{idxSelection/dimension,idxSelection%dimension};
        int pieceIdx = indexPieceEn(src);
        auto mouvementsInitiaux = pieces[pieceIdx]->deplacementsValides();
        std::vector<Position> mouvements;
        for(auto& m : mouvementsInitiaux){
            int occ = indexPieceEn(m);
            if (occ!=-1 && estBlanc(occ)==estBlanc(pieceIdx)) continue;
            bool glisse = dynamic_cast<model::Tour*>(pieces[pieceIdx].get())
                          || dynamic_cast<model::Fou*>(pieces[pieceIdx].get())
                          || dynamic_cast<model::Dame*>(pieces[pieceIdx].get());
            if (glisse && estBloqueEntre(src,m)) continue;
            mouvements.push_back(m);
        }
        boutons[idxSelection]->setStyleSheet(styleCase(src.first,src.second));
        if (std::find(mouvements.begin(),mouvements.end(),clic)==mouvements.end()){
            QMessageBox::warning(this, "Mouvement","Non valide");
        }
        else {
            int destOcc = indexPieceEn(clic);
            if (destOcc != -1 && dynamic_cast<model::Roi*>(pieces[destOcc].get())){
                QMessageBox::information(this,"Fin", "Roi capturé. Fin du jeu.");
                partieTerminee=true;
            }
            if (destOcc != - 1) {
                pieces.erase(pieces.begin()+destOcc); estBlancVecteur.erase(estBlancVecteur.begin()+destOcc);
                if (destOcc<pieceIdx) --pieceIdx;
            }

            pieces[pieceIdx]->setPosition(clic);
            tourBlanc =! tourBlanc;
            afficherPieces(); afficherTour();
        }

        idxSelection=-1;
    }
}

}
