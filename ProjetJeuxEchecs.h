#pragma once
#include <QtWidgets/QMainWindow>
#include <vector>
#include <memory>
#include "Piece.h"
#include <QtWidgets/QPushButton>

namespace gui {

class ProjetJeuxEchecs : public QMainWindow {
    Q_OBJECT

public:
    explicit ProjetJeuxEchecs(QWidget* parent = nullptr);
    ~ProjetJeuxEchecs() override;

private slots:
    void caseCliquee(int indice);

private:
    void initialiserPieces();
    void afficherPieces();
    QString styleCase(int ligne, int colonne) const;

    static constexpr int dimension = 8;
    std::vector<std::unique_ptr<model::Piece>> piecesEchecs;
    std::vector<QPushButton*> boutons;
    int indiceSelection = -1;
    bool tourBlanc = true;
    bool partieTerminee = false;
};

} // namespace gui

