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
    void caseCliquee(int idx);

private:
    void initialiserPieces();
    void afficherPieces();
    void afficherTour();
    QString styleCase(int l, int c) const;
    int indexPieceEn(model::Position pos) const;
    bool estBloqueEntre(model::Position src, model::Position dest) const;
    bool estBlanc(size_t i) const { return estBlancVecteur[i]; }
    static constexpr int dimension = 8;
    std::vector<std::unique_ptr<model::Piece>> pieces;
    std::vector<bool> estBlancVecteur;
    std::vector<QPushButton*> boutons;
    QLabel* etiquetteTour;
    int idxSelection = -1;
    bool tourBlanc = true;
    bool partieTerminee = false;
};
}
