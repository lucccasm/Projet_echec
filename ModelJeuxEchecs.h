#pragma once

#include <QObject>
#include "Piece.h"
#include <vector>
#include <optional>
#include <utility>


namespace model {

using Position = std::pair<int,int>;

enum class StatutMouvement { NonValide, OK, RoiCapture };

class ModelJeuxEchecs : public QObject {
    Q_OBJECT

public:
    explicit ModelJeuxEchecs(QObject* parent = nullptr);

    void nouvellePartie();
    void nouvellePartieRapide();

    std::optional<size_t> obtenirIndice(const Position& pos) const;
    std::vector<Position> deplacementsLegaux(const Position& src) const;
    StatutMouvement deplacer(const Position& src, const Position& dest);

    size_t nombrePieces() const;
    const Piece& piece(size_t idx) const;
    bool estBlanc(size_t idx) const;
    bool tourBlanc() const;
    bool partieTerminee() const;
    bool estEnEchec(bool roiBlanc) const;
    bool estEchecEtMat(bool roiBlanc) const;
    bool metEnEchecPropreRoi(const Position& src, const Position& dest);

signals:
    void partieInitialisee();
    void pieceDeplacee(const Position& src, const Position& dest);
    void tourChangee(bool tourBlanc);
    void partieTermineeSignal();
    void erreurRoi(const QString& message);
    void roiEnEchec(bool roiBlanc);
    void roiEnEchecEtMat(bool roiBlanc);


private:
    bool estBloque(const Position& source, const Position& dest) const;
    void ajouterRoiSiValide(const Position& pos, bool estBlanc);

    std::vector<std::unique_ptr<Piece>> pieces_;
    bool tourBlanc_;
    bool partieTerminee_;
};

}
