#include <iostream>
#include <vector>
#include "fichier/fichier.h"
#include "plateau/tuile/tuile.h"
#include "plateau/plateau.h"

using namespace std;

bool resoudreSequentiel(Plateau& plateau, int tuileIndex, vector<bool> tuilesUtilisees);

int main() {
    Fichier fichier("5_5.txt");
    vector<string> file = fichier.readFile();

    Plateau plateau(file);
    plateau.afficherListeTuiles();

    vector<Tuile> listeTuiles = plateau.getListeTuiles();
    // Vérifier si la tuile est valide après erase
//    listeTuiles.begin()->afficher();
//    cout << listeTuiles.size() << endl;
//    listeTuiles.erase(listeTuiles.begin() + 1);
//    (listeTuiles.begin()+1)->afficher();
//    cout << listeTuiles.size() << endl;

//    cout << algorithmeSequentiel(plateau, vector<bool>(listeTuiles.size(), false)) << endl;
    resoudreSequentiel(plateau, 0, vector<bool>(listeTuiles.size(), false));

    plateau.afficher();

    return 0;
}

bool resoudreSequentiel(Plateau& plateau, int tuileIndex, vector<bool> tuilesUtilisees) {
    if (tuileIndex == plateau.getTotalRows() * plateau.getTotalColumns()) {
        return true;
    }

    for (int i = 0; i < plateau.getListeTuiles().size(); i++) {
        if (!plateau.isTuileUtilisee(tuilesUtilisees, i)) {
            plateau.pushTuile(i);

            if (plateau.verifyTuile()) {
//                plateau.setTuileUtilisee(i, true); // Marquez la tuile comme utilisée
                tuilesUtilisees[i] = true;
                if (resoudreSequentiel(plateau, tuileIndex + 1, tuilesUtilisees)) {
                    return true;
                }
                tuilesUtilisees[i] = false;
//                plateau.setTuileUtilisee(i, false); // Réinitialisez l'état de la tuile
            }
            plateau.popTuile();
        }
    }
    return false;
}