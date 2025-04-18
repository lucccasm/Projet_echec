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

ProjetJeuxEchecs::ProjetJeuxEchecs(QWidget* parent)
    : QMainWindow(parent), idxSelection(-1), tourBlanc(true), partieTerminee(false)
{
    auto* central = new QWidget(this);
    setCentralWidget(central);
    auto* layoutPrincipal = new QHBoxLayout(central);

    auto* grille = new QGridLayout(); grille->setSpacing(0);
    for (int r=0; r<dimension; ++r) {
        for (int c=0; c<dimension; ++c) {
            auto* btn = new QPushButton(this);
            btn->setFixedSize(60,60);
            btn->setStyleSheet(styleCase(r,c));
            grille->addWidget(btn, r, c);
            int idx = r*dimension + c;
            boutons.push_back(btn);
            connect(btn, &QPushButton::clicked, this, [this,idx]{ caseCliquee(idx); });
        }
    }
    layoutPrincipal->addLayout(grille);

    auto* menu = new QVBoxLayout();
    etiquetteTour = new QLabel(this);
    etiquetteTour->setAlignment(Qt::AlignCenter);
    menu->addWidget(etiquetteTour);
    auto* btnNew = new QPushButton("Nouvelle Partie", this);
    auto* btnQuit = new QPushButton("Quitter", this);
    menu->addWidget(btnNew);
    menu->addWidget(btnQuit);
    menu->addStretch();
    layoutPrincipal->addLayout(menu);

    connect(btnNew, &QPushButton::clicked, this, [this]{
        tourBlanc=true; partieTerminee=false; idxSelection=-1;
        initialiserPieces(); afficherPieces(); afficherTour();
    });
    connect(btnQuit, &QPushButton::clicked, this, &QMainWindow::close);

    initialiserPieces(); afficherPieces(); afficherTour();
}

ProjetJeuxEchecs::~ProjetJeuxEchecs() = default;

QString ProjetJeuxEchecs::styleCase(int l, int c) const {
    return ((l+c)%2==0) ? "background-color:#EEE;" : "background-color:#555;";
}

void ProjetJeuxEchecs::afficherTour() {
    etiquetteTour->setText(
        QString("C'est le tour du joueur %1").arg(tourBlanc?"Blanc":"Noir")
        );
}

void ProjetJeuxEchecs::initialiserPieces() {
    pieces.clear();
    // Blancs
    pieces.emplace_back(std::make_unique<model::Tour>(Position{0,0}));
    pieces.emplace_back(std::make_unique<model::Cavalier>(Position{0,1}));
    pieces.emplace_back(std::make_unique<model::Fou>(Position{0,2}));
    pieces.emplace_back(std::make_unique<model::Dame>(Position{0,3}));
    pieces.emplace_back(std::make_unique<model::Roi>(Position{0,4}));
    pieces.emplace_back(std::make_unique<model::Fou>(Position{0,5}));
    pieces.emplace_back(std::make_unique<model::Cavalier>(Position{0,6}));
    pieces.emplace_back(std::make_unique<model::Tour>(Position{0,7}));
    for(int i=0; i<8; ++i)
        pieces.emplace_back(std::make_unique<model::Pion>(Position{1,i}, true));
    // Noirs
    pieces.emplace_back(std::make_unique<model::Tour>(Position{7,0}));
    pieces.emplace_back(std::make_unique<model::Cavalier>(Position{7,1}));
    pieces.emplace_back(std::make_unique<model::Fou>(Position{7,2}));
    pieces.emplace_back(std::make_unique<model::Dame>(Position{7,3}));
    pieces.emplace_back(std::make_unique<model::Roi>(Position{7,4}));
    pieces.emplace_back(std::make_unique<model::Fou>(Position{7,5}));
    pieces.emplace_back(std::make_unique<model::Cavalier>(Position{7,6}));
    pieces.emplace_back(std::make_unique<model::Tour>(Position{7,7}));
    for(int i=0; i<8; ++i)
        pieces.emplace_back(std::make_unique<model::Pion>(Position{6,i}, false));
}

void ProjetJeuxEchecs::afficherPieces() {
    // Réinitialiser chaque case
    for (int i = 0; i < dimension*dimension; ++i) {
        int r = i / dimension, c = i % dimension;
        boutons[i]->setText("");
        boutons[i]->setStyleSheet(styleCase(r, c));
    }

    // Afficher chaque pièce
    for (size_t i = 0; i < pieces.size(); ++i) {
        auto [r, c] = pieces[i]->getPosition();
        QPushButton* b = boutons[r*dimension + c];

        // Choix de la lettre (toujours majuscule)
        char lettre = '?';
        if (dynamic_cast<model::Tour*>(pieces[i].get()))      lettre = 'T';
        else if (dynamic_cast<model::Cavalier*>(pieces[i].get())) lettre = 'C';
        else if (dynamic_cast<model::Fou*>(pieces[i].get()))      lettre = 'F';
        else if (dynamic_cast<model::Dame*>(pieces[i].get()))     lettre = 'D';
        else if (dynamic_cast<model::Roi*>(pieces[i].get()))      lettre = 'R';
        else if (dynamic_cast<model::Pion*>(pieces[i].get()))     lettre = 'P';

        // Déterminer la couleur du texte :
        // Supposons que les 16 premières pièces du vecteur sont Blanches
        bool estBlanc = (i < 16);
        QString couleurTexte = estBlanc ? "white" : "black";

        b->setText(QString(lettre));
        b->setStyleSheet(
            styleCase(r, c) +
            QString("font-size:20px; color:%1;").arg(couleurTexte)
            );
    }
}

void ProjetJeuxEchecs::caseCliquee(int idx) {
    if (partieTerminee) return;

    int r = idx / dimension;
    int c = idx % dimension;
    Position clic{r, c};

    if (idxSelection < 0) {
        // === Phase de sélection ===
        // On cherche l'indice de la pièce cliquée
        for (size_t i = 0; i < pieces.size(); ++i) {
            if (pieces[i]->getPosition() == clic) {
                // Déterminer la couleur de la pièce :
                // on assume les 16 premières sont Blanches
                bool estBlanc = (i < 16);
                if ((tourBlanc && estBlanc) || (!tourBlanc && !estBlanc)) {
                    // OK, on sélectionne
                    afficherPieces();
                    afficherTour();
                    idxSelection = idx;
                    // bordure rouge sur la case sélectionnée
                    boutons[idx]->setStyleSheet(
                        boutons[idx]->styleSheet() + "border:2px solid red;"
                        );
                    // surligner déplacements possibles
                    auto moves = pieces[i]->deplacementsValides();
                    if (moves.empty()) {
                        QMessageBox::warning(
                            this,
                            "Bloqué",
                            "Cette pièce ne peut pas bouger."
                            );
                        idxSelection = -1;
                    } else {
                        for (auto& p : moves) {
                            int id = p.first * dimension + p.second;
                            boutons[id]->setStyleSheet(
                                boutons[id]->styleSheet()
                                + "border:2px solid green;"
                                );
                        }
                    }
                } else {
                    // Mauvais tour
                    QMessageBox::warning(
                        this,
                        "Tour",
                        "Ce n'est pas votre tour !"
                        );
                }
                return;
            }
        }
        // si on ne clique pas sur une pièce, on ne fait rien
        return;
    }

    // === Phase de déplacement ===
    // On retrouve la pièce sélectionnée
    Position src { idxSelection / dimension, idxSelection % dimension };
    size_t pieceIdx = 0;
    for (; pieceIdx < pieces.size(); ++pieceIdx) {
        if (pieces[pieceIdx]->getPosition() == src) break;
    }

    // Récupérer ses déplacements valides
    auto moves = pieces[pieceIdx]->deplacementsValides();
    // Restauration du style de la case source
    boutons[idxSelection]->setStyleSheet(
        styleCase(src.first, src.second)
        );

    // Vérifier si dest est dans moves
    if (std::find(moves.begin(), moves.end(), clic) == moves.end()) {
        QMessageBox::warning(
            this,
            "Mouvement",
            "Mouvement non valide pour cette pièce."
            );
        // on réaffiche tout sans changer de tour
        afficherPieces(); afficherTour();
        idxSelection = -1;
        return;
    }

    // Déplacement autorisé -> exécution
    pieces[pieceIdx]->setPosition(clic);

    // Vérifier capture du roi adverse
    for (size_t j = 0; j < pieces.size(); ++j) {
        if (j != pieceIdx && pieces[j]->getPosition() == clic) {
            if (dynamic_cast<model::Roi*>(pieces[j].get())) {
                QMessageBox::information(
                    this,
                    "Fin de partie",
                    QString("Le joueur %1 a capturé le roi. Fin du jeu.")
                        .arg(tourBlanc ? "Blanc" : "Noir")
                    );
                partieTerminee = true;
            }
            pieces.erase(pieces.begin() + j);
            if (j < pieceIdx) --pieceIdx;
            break;
        }
    }

    // Changer de tour
    tourBlanc = !tourBlanc;

    // Refresh
    afficherPieces();
    afficherTour();
    idxSelection = -1;
}

} // namespace gui

