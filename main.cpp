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

    plateau.getTuile(0, 0).afficher();
    cout << plateau.getTuile(0, 0).getCouleurDroite() << endl;
    return 0;
}