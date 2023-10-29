#ifndef MACMAHON_PLATEAU_H
#define MACMAHON_PLATEAU_H

#include "../fichier/fichier.h"
#include "tuile/tuile.h"

using namespace std;

class Plateau {
public:
    Plateau(vector<string> fichier);
    void afficher();
    void remplir();
    Tuile getTuile(int row, int column);

private:
    int rows_;
    int columns_;
    vector<string> fichier_;
    vector<vector<Tuile>> plateau_;
};

#endif // MACMAHON_PLATEAU_H
