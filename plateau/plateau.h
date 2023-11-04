#ifndef MACMAHON_PLATEAU_H
#define MACMAHON_PLATEAU_H

#include "../fichier/fichier.h"
#include "tuile/tuile.h"

using namespace std;

class Plateau {
public:
    Plateau(vector<string> fichier);
    void afficher();
    void afficherListeTuiles();
    void remplirListeTuiles(vector<string> fichier);
    void pushTuile(int index);
    void popTuile(int row, int column);
    Tuile getCurrentTuile();

    bool verifyTuile();
    bool verifyTuileForAngle();
    bool verifyCouleursBordure();
    bool verifyCouleursAngles();
    bool verifyCouleursVoisins();

private:
    int totalRows_;
    int totalColumns_;

    vector<Tuile> listeTuiles_;
    vector<vector<Tuile>> plateau_;

    // Tuile sélectionnée dans la liste des tuiles
    Tuile selectedTuile_;
    int selectedTuileIterator_;

    // Tuile actuelle dans le plateau (que je m'apprête à actualiser)
    Tuile currentTuile_;
    int currentRow_;
    int currentColumn_;

    int nextRow_;
    int nextColumn_;

    Tuile defaultTuile_ = Tuile();

    char bordureCouleur = 'N';
};

#endif // MACMAHON_PLATEAU_H
