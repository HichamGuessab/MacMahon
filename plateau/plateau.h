#ifndef MACMAHON_PLATEAU_H
#define MACMAHON_PLATEAU_H

#include "../fichier/fichier.h"
#include "tuile/tuile.h"
#include <vector>

using namespace std;

class Plateau {
public:
    Plateau(vector<string> file);
    void fillListTuiles(vector<string> file);
    void pushTuile(int index);
    void popTuile();

    int getTotalRows();
    int getTotalColumns();

    Tuile getCurrentTuile();
    vector<Tuile> getListTuiles();
    bool isTuileUsed(vector<bool> tuilesUsed, int index);

    bool verifyTuile();
    bool verifyTuileForCorner();
    bool verifyBordersColors();
    bool verifyCornersColors();
    bool verifyNeighborsColors();

    vector<vector<Tuile>> getPlateau();

    void display();
    void displayListTuiles();

private:
    int totalRows_;
    int totalColumns_;

    vector<Tuile> listTuiles_;
    vector<vector<Tuile>> plateau_;

    // Tuile actuelle dans le plateau (que je m'apprête à actualiser)
    Tuile currentTuile_;
    int currentRow_;
    int currentColumn_;

    int nextRow_;
    int nextColumn_;

    Tuile defaultTuile_ = Tuile();

    char borderColor;
};

#endif // MACMAHON_PLATEAU_H
