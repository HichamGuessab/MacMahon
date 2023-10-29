#include <iostream>
#include <vector>
#include "fichier/fichier.h"
#include "plateau/tuile/tuile.h"
#include "plateau/plateau.h"

using namespace std;

int main() {
    Fichier fichier("5_5.txt");
    vector<string> file = fichier.readFile();

    Plateau plateau(file);
    plateau.remplir();
    plateau.afficher();

    cout << endl;
    cout << endl;

    plateau.switchTuiles(plateau.getTuileAddress(0, 0), plateau.getTuileAddress(0, 1));

    plateau.afficher();

    return 0;
}