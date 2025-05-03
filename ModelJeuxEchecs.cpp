#include "ModelJeuxEchecs.h"
#include "DeplacementTemporaire.h"
#include "Tour.h"
#include "Cavalier.h"
#include "Fou.h"
#include "Dame.h"
#include "Roi.h"
#include "Pion.h"

namespace model {

ModelJeuxEchecs::ModelJeuxEchecs(QObject* parent) : QObject(parent) {}

void ModelJeuxEchecs::ajouterRoiSiValide(const Position& pos, bool estBlanc)
{
    bool positionValide =
        (!estBlanc && pos.first == 0 && pos.second == 4)
        || ( estBlanc && pos.first == 7 && pos.second == 4);
    if (!positionValide) {
        emit erreurRoi(
            QString("Position ou couleur de roi invalide : (%1,%2)")
                .arg(pos.first).arg(pos.second)
            );
        return;
    }

    try {
        pieces_.push_back(std::make_unique<Roi>(pos, estBlanc));
    }
    catch (const RoiException& e) {
        emit erreurRoi(QString::fromStdString(e.what()));
    }
}

void ModelJeuxEchecs::nouvellePartie()
{
    pieces_.clear();
    tourBlanc_ = true;
    partieTerminee_ = false;

    pieces_.push_back(std::make_unique<Tour>(Position{0,0}, false));
    pieces_.push_back(std::make_unique<Cavalier>(Position{0,1}, false));
    pieces_.push_back(std::make_unique<Fou>(Position{0,2}, false));
    pieces_.push_back(std::make_unique<Dame>(Position{0,3}, false));
    ajouterRoiSiValide({0,4}, false);
    pieces_.push_back(std::make_unique<Fou>(Position{0,5}, false));
    pieces_.push_back(std::make_unique<Cavalier>(Position{0,6}, false));
    pieces_.push_back(std::make_unique<Tour>(Position{0,7}, false));

    for(int c = 0; c < 8; ++c) {
        pieces_.push_back(std::make_unique<Pion>(Position{1,c}, false));
    }

    for(int c = 0; c < 8; ++c) {
        pieces_.push_back(std::make_unique<Pion>(Position{6,c}, true));
    }

    pieces_.push_back(std::make_unique<Tour>(Position{7,0}, true));
    pieces_.push_back(std::make_unique<Cavalier>(Position{7,1}, true));
    pieces_.push_back(std::make_unique<Fou>(Position{7,2}, true));
    pieces_.push_back(std::make_unique<Dame>(Position{7,3}, true));
    ajouterRoiSiValide({7,4}, true);
    pieces_.push_back(std::make_unique<Fou>(Position{7,5}, true));
    pieces_.push_back(std::make_unique<Cavalier>(Position{7,6}, true));
    pieces_.push_back(std::make_unique<Tour>(Position{7,7}, true));

    emit partieInitialisee();
}

std::optional<size_t> ModelJeuxEchecs::obtenirIndice(const Position& pos) const
{
    for(size_t i = 0; i < pieces_.size(); ++i)
        if(pieces_[i]->obtenirPosition() == pos)
            return i;
    return std::nullopt;
}

bool ModelJeuxEchecs::estBloque(const Position& source, const Position& dest) const
{
    int dL = (dest.first > source.first) ? 1 : (dest.first < source.first) ? -1 : 0;
    int dC = (dest.second > source.second) ? 1 : (dest.second < source.second) ? -1 : 0;
    Position cur = source;
    while(cur != dest) {
        cur.first += dL; cur.second += dC;
        if(cur != dest && obtenirIndice(cur).has_value()) return true;
    }
    return false;
}

std::vector<Position> ModelJeuxEchecs::deplacementsLegaux(const Position& src) const
{

    std::vector<Position> filt;
    auto opt = obtenirIndice(src);
    if(!opt) return {};
    size_t idx = *opt;
    auto& srcPiece = pieces_[idx];
    bool srcBlanc = srcPiece->obtenirEstBlanc();
    auto brut = srcPiece->deplacementsValides();
    for(auto& p : brut) {
        auto occ = obtenirIndice(p);
        if (occ && pieces_[*occ]->obtenirEstBlanc() == srcBlanc)
            continue;

        if (dynamic_cast<const Pion*>(pieces_[idx].get())) {
            int dL = p.first  - src.first;
            int dC = p.second - src.second;
            int direction = srcBlanc ? -1 : +1;

            if (dC == 0) {
                if (occ)
                    continue;

                if (dL == 2 * direction) {
                    Position interm{ src.first + direction, src.second };
                    if (obtenirIndice(interm).has_value())
                        continue;
                }
            }
            else {
                if (!occ)
                    continue;
            }
        }

        bool gl = dynamic_cast<const Tour*>(pieces_[idx].get())
                  || dynamic_cast<const Fou*>(pieces_[idx].get())
                  || dynamic_cast<const Dame*>(pieces_[idx].get());
        if(gl && estBloque(src, p)) continue;
        filt.push_back(p);
    }
    return filt;
}

StatutMouvement ModelJeuxEchecs::deplacer(const Position& src, const Position& dest)
{
    if(partieTerminee_) return StatutMouvement::NonValide;
    auto coups = deplacementsLegaux(src);

    if(std::find(coups.begin(), coups.end(), dest) == coups.end())
        return StatutMouvement::NonValide;
    auto occ = obtenirIndice(dest);

    if(occ) {
        if(dynamic_cast<Roi*>(pieces_[*occ].get())) partieTerminee_ = true;
        pieces_.erase(pieces_.begin() + *occ);
    }

    size_t idx = *obtenirIndice(src);
    pieces_[idx]->definirPosition(dest);
    tourBlanc_ = !tourBlanc_;
    bool ancienJoueurBlanc = !tourBlanc_;

    emit pieceDeplacee(src, dest);
    emit tourChangee(tourBlanc_);

    bool roiEnDangerBlanc = tourBlanc_;
    if (estEnEchec(roiEnDangerBlanc)) {
        emit roiEnEchec(roiEnDangerBlanc);
        if (estEchecEtMat(roiEnDangerBlanc))
            emit roiEnEchecEtMat(roiEnDangerBlanc);
    }

    if (estEnEchec(ancienJoueurBlanc)) {
        emit roiEnEchec(ancienJoueurBlanc);
        if (estEchecEtMat(ancienJoueurBlanc))
            emit roiEnEchecEtMat(ancienJoueurBlanc);
    }

    if (partieTerminee_)
        emit partieTermineeSignal();
    return partieTerminee_ ? StatutMouvement::RoiCapture : StatutMouvement::OK;
}

bool ModelJeuxEchecs::estEnEchec(bool roiBlanc) const
{
    Position posRoi{-1,-1};
    for (auto& p : pieces_) {
        if (auto r = dynamic_cast<Roi*>(p.get()); r && p->obtenirEstBlanc() == roiBlanc) {
            posRoi = r->obtenirPosition();
            break;
        }
    }
    for (size_t i = 0; i < pieces_.size(); ++i) {
        if (pieces_[i]->obtenirEstBlanc() != roiBlanc) {
            auto coups = pieces_[i]->deplacementsValides();
            if (std::find(coups.begin(), coups.end(), posRoi) != coups.end())
                return true;
        }
    }
    return false;
}

bool ModelJeuxEchecs::estEchecEtMat(bool roiBlanc) const
{
    if (!estEnEchec(roiBlanc))
        return false;

    for (size_t i = 0; i < pieces_.size(); ++i) {
        if (pieces_[i]->obtenirEstBlanc() != roiBlanc)
            continue;

        auto src = pieces_[i]->obtenirPosition();
        auto coups = deplacementsLegaux(src);

        for (auto& dest : coups) {
            Position anciennePos = src;
            auto occ = obtenirIndice(dest);
            Piece* capt = nullptr;
            Position captAnicennePos;
            if (occ) {
                capt = pieces_[*occ].get();
                captAnicennePos = capt->obtenirPosition();
                capt->definirPosition({-1,-1});
            }
            pieces_[i]->definirPosition(dest);

            bool encoreEnEchec = estEnEchec(roiBlanc);

            pieces_[i]->definirPosition(anciennePos);
            if (capt) {
                capt->definirPosition(captAnicennePos);
            }

            if (!encoreEnEchec)
                return false;
        }
    }
    return true;
}

bool ModelJeuxEchecs::metEnEchecPropreRoi(const Position& src, const Position& dest)
{
    auto idx = obtenirIndice(src);
    if (!idx) return false;
    size_t i = *idx;
    bool couleur = pieces_[i]->obtenirEstBlanc();

    Position anciennePos = pieces_[i]->obtenirPosition();
    auto occ = obtenirIndice(dest);
    std::unique_ptr<Piece> capt;
    if (occ) {
        capt = std::move(pieces_[*occ]);
        pieces_.erase(pieces_.begin()+*occ);
        if (*occ < i) --i;
    }
    pieces_[i]->definirPosition(dest);
    bool enEchec = estEnEchec(couleur);
    pieces_[i]->definirPosition(anciennePos);
    if (capt) {
        pieces_.insert(pieces_.begin()+*occ, std::move(capt));
    }
    return enEchec;
}

size_t ModelJeuxEchecs::nombrePieces() const { return pieces_.size(); }
const Piece& ModelJeuxEchecs::piece(size_t idx) const { return *pieces_[idx]; }

bool ModelJeuxEchecs::estBlanc(size_t idx) const { return pieces_[idx]->obtenirEstBlanc(); }
bool ModelJeuxEchecs::tourBlanc() const { return tourBlanc_; }
bool ModelJeuxEchecs::partieTerminee() const { return partieTerminee_; }

}
