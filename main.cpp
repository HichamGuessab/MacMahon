#include <iostream>
#include <vector>
#include "fichier.h"
#include "tuile.h"
#include "plateau.h"

using namespace std;

int main() {
    Fichier fichier("5_5.txt");
    vector<string> file = fichier.readFile();

    Plateau plateau(file);
    plateau.remplir();
    plateau.afficher();
    return 0;
}