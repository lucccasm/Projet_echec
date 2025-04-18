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

    static constexpr int dimension = 8;
    std::vector<std::unique_ptr<model::Piece>> pieces;
    std::vector<QPushButton*> boutons;
    QLabel* etiquetteTour;
    int idxSelection = -1;
    bool tourBlanc = true;
    bool partieTerminee = false;
};

} // namespace gui
