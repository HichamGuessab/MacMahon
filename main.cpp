#include <iostream>
#include <utility>
#include <vector>
#include <chrono>
#include <thread>

#include "fichier/fichier.h"
#include "plateau/tuile/tuile.h"
#include "plateau/plateau.h"

using namespace std;

bool resoudreSequentiel(Plateau& plateau, int tuileIndex, vector<bool> tuilesUtilisees);
bool resoudreByThreads(Plateau& plateauFinal, Plateau plateau, int tuileIndex, vector<bool> tuilesUtilisees, bool &resolved);
void threadLauncher(Plateau& plateauFinal, Plateau plateau, int tuileIndex, vector<bool> tuilesUtilisees, bool& resolved);
bool lancerThreads(Plateau& plateauFinal, Plateau plateau, int tuileIndex, vector<bool> tuilesUtilisees);

int main() {
    Fichier fichier("5_5.txt");
    vector<string> file = fichier.readFile();

    Plateau plateau(file);
    Plateau plateauFinal(file);

    vector<Tuile> listeTuiles = plateau.getListeTuiles();

    auto start = std::chrono::high_resolution_clock::now();

    bool resolved = false;
    lancerThreads(plateauFinal, plateau, 0, vector<bool>(listeTuiles.size(), resolved));

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    plateauFinal.afficher();

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
                tuilesUtilisees[i] = true;
                if (resoudreSequentiel(plateau, tuileIndex + 1, tuilesUtilisees)) {
                    return true;
                }
                tuilesUtilisees[i] = false;
            }
            plateau.popTuile();
        }
    }
    return false;
}

bool lancerThreads(Plateau& plateauFinal, Plateau plateau, int tuileIndex, vector<bool> tuilesUtilisees) {
    bool resolved = false;
    // J'ai x tuiles, elle sera lancé x fois dans x threads
    // Chaque thread aura une tuile différente
    int nbTuiles = plateau.getListeTuiles().size();
    vector<thread> threads(nbTuiles);

    for (int i = 0; i < nbTuiles; i++) {
        plateau.pushTuile(i);
        if (plateau.verifyTuile()) {
            tuilesUtilisees[i] = true;
            cout << "Tuile i : " << i << " est utilisée" << endl;
            threads[i] = thread(threadLauncher, ref(plateauFinal), plateau, tuileIndex, tuilesUtilisees, ref(resolved));
            tuilesUtilisees[i] = false;
        }
        plateau.popTuile();
    }
    for(int i = 0; i < nbTuiles; i++) {
        if(threads[i].joinable()) {
            threads[i].join();
        }
    }
    return false;
}

void threadLauncher(Plateau& plateauFinal, Plateau plateau, int tuileIndex, vector<bool> tuilesUtilisees, bool& resolved) {
    if(resolved) {
        return;
    } else {
        Plateau plateauX = plateau;
        if(resoudreByThreads(plateauFinal, plateau, tuileIndex + 1, std::move(tuilesUtilisees), resolved)) {
            return;
        }
    }
}

bool resoudreByThreads(Plateau& plateauFinal, Plateau plateau, int tuileIndex, vector<bool> tuilesUtilisees, bool& resolved) {
    if(resolved) {
        return false;
    }
    if (tuileIndex == plateau.getTotalRows() * plateau.getTotalColumns()) {
        plateauFinal = plateau;
        resolved = true;
        return true;
    }

    for (int i = 0; i < plateau.getListeTuiles().size(); i++) {
        if (!plateau.isTuileUtilisee(tuilesUtilisees, i)) {
            plateau.pushTuile(i);

            if (plateau.verifyTuile()) {
                tuilesUtilisees[i] = true;
                if (resoudreByThreads(plateauFinal, plateau, tuileIndex + 1, tuilesUtilisees, resolved)) {
                    return true;
                }
                tuilesUtilisees[i] = false;
            }
            plateau.popTuile();
        }
    }
    return false;
    // g++ main.cpp plateau/plateau.cpp plateau/tuile/tuile.cpp fichier/fichier.cpp -o main -l pthread
}