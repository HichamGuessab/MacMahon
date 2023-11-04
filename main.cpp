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

    for (int i = 0; i < 25; i++) {
        cout << "-----------------" << endl;
        plateau.pushTuile(i);
        if(plateau.verifyTuile()) {
            plateau.getCurrentTuile().afficher();
        }
    }
    plateau.popTuile();
    plateau.popTuile();
    plateau.popTuile();
    plateau.popTuile();
    plateau.pushTuile(  2);
    plateau.popTuile();
    plateau.popTuile();
    plateau.afficher();

    return 0;
}