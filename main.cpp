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

    return 0;
}