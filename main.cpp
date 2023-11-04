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
    plateau.afficherListeTuiles();

    cout << endl;

    plateau.pushTuile(0);
    plateau.afficher();
    cout << plateau.getCurrentTuile().isTuileVide() << endl;

    plateau.popTuile(0, 0);
    cout << endl;
    cout << endl;
    plateau.afficher();

    cout << plateau.getCurrentTuile().isTuileVide() << endl;

    return 0;
}