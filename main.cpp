#include <iostream>
#include <vector>
#include "fichier/fichier.h"
#include "plateau/tuile/tuile.h"
#include "plateau/plateau.h"

using namespace std;

bool resoudreSequentiel(Plateau& plateau, int tuileIndex, vector<bool> tuilesUtilisees);

int main() {
    Fichier fichier("4_4.txt");
    vector<string> file = fichier.readFile();

    Plateau plateau(file);

    vector<Tuile> listeTuiles = plateau.getListeTuiles();

    auto start = std::chrono::high_resolution_clock::now();

    resoudreSequentiel(plateau, 0, vector<bool>(listeTuiles.size(), false));

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    plateau.afficher();

    std::cout << "Temps d'éxecution: " << duration << " millisecondes" << std::endl;

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