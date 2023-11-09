#include <iostream>
#include <utility>
#include <vector>
#include <chrono>
#include <thread>

#include "fichier/fichier.h"
#include "plateau/tuile/tuile.h"
#include "plateau/plateau.h"

using namespace std;

bool sequentialRecursiveResolver(Plateau& plateau, int tuileIndex, vector<bool> tuilesUsed);

bool threadsManager(Plateau& finalPlateau, Plateau plateau, int tuileIndex, vector<bool> tuilesUsed);
void threadLauncher(Plateau& finalPlateau, Plateau plateau, int tuileIndex, vector<bool> tuilesUsed, bool& resolved);
bool threadsRecursiveResolver(Plateau& finalPlateau, Plateau plateau, int tuileIndex, vector<bool> tuilesUsed, bool &resolved);

bool threadsPoolManager(Plateau& finalPlateau, Plateau plateau, int tuileIndex, vector<bool> tuilesUsed);
void threadPoolLauncher(Plateau& finalPlateau, Plateau plateau, int tuileIndex, vector<bool> tuilesUsed, bool& resolved);

int cpt = 0;
const int MAX_THREADS = 10;

// g++ main.cpp plateau/plateau.cpp plateau/tuile/tuile.cpp fichier/fichier.cpp -o main -l pthread

int main() {
    Fichier fichier("5_5.txt");
    vector<string> file = fichier.readFile();

    Plateau plateau(file);
    Plateau plateauFinal(file);

    vector<Tuile> listeTuiles = plateau.getListTuiles();

    auto start = std::chrono::high_resolution_clock::now();

    bool resolved = false;
//    sequentialRecursiveResolver(plateauFinal, 0, vector<bool>(listeTuiles.size()));
    threadsManager(plateauFinal, plateau, 0, vector<bool>(listeTuiles.size(), resolved));
//    threadsPoolManager(plateauFinal, plateau, 0, vector<bool>(listeTuiles.size(), resolved));

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    plateauFinal.display();

    std::cout << "Temps d'éxecution: " << duration << " millisecondes" << std::endl;

    return 0;
}

bool sequentialRecursiveResolver(Plateau& plateau, int tuileIndex, vector<bool> tuilesUsed) {
    if (tuileIndex == plateau.getTotalRows() * plateau.getTotalColumns()) {
        return true;
    }

    for (int i = 0; i < plateau.getListTuiles().size(); i++) {
        if (!plateau.isTuileUsed(tuilesUsed, i)) {
            plateau.pushTuile(i);

            if (plateau.verifyTuile()) {
                tuilesUsed[i] = true;
                if (sequentialRecursiveResolver(plateau, tuileIndex + 1, tuilesUsed)) {
                    return true;
                }
                tuilesUsed[i] = false;
            }
            plateau.popTuile();
        }
    }
    return false;
}

bool threadsManager(Plateau& finalPlateau, Plateau plateau, int tuileIndex, vector<bool> tuilesUsed) {
    bool resolved = false;
    // J'ai x tuiles, elle sera lancé x fois dans x threads
    // Chaque thread aura une tuile différente
    int nbTuiles = plateau.getListTuiles().size();
    vector<thread> threads(nbTuiles);

    for (int i = 0; i < nbTuiles; i++) {
        plateau.pushTuile(i);
//        if (plateau.verifyTuile()) {
            tuilesUsed[i] = true;
            cout << "Tuile i : " << i << " est utilisée" << endl;
            threads[i] = thread(threadLauncher, ref(finalPlateau), plateau, tuileIndex, tuilesUsed, ref(resolved));
        tuilesUsed[i] = false;
//        }
        plateau.popTuile();
    }
    for(int i = 0; i < nbTuiles; i++) {
        if(threads[i].joinable()) {
            threads[i].join();
        }
    }
    return false;
}

void threadLauncher(Plateau& finalPlateau, Plateau plateau, int tuileIndex, vector<bool> tuilesUsed, bool& resolved) {
    if(resolved) {
        return;
    } else {
        Plateau plateauX = plateau;
        if(threadsRecursiveResolver(finalPlateau, plateau, tuileIndex + 1, std::move(tuilesUsed), resolved)) {
            return;
        }
    }
}

bool threadsPoolManager(Plateau& finalPlateau, Plateau plateau, int tuileIndex, vector<bool> tuilesUsed) {
    cpt = 0;
    bool resolved = false;
    // J'ai x tuiles, elle sera lancé x fois dans x threads
    // Chaque thread aura une tuile différente
    int nbTuiles = plateau.getListTuiles().size();
    vector<thread> threads(nbTuiles);

    int index = 0;
    while (index < nbTuiles && !resolved) {
        if(cpt < MAX_THREADS) {
            plateau.pushTuile(index);
//            if (plateau.verifyTuile()) {
                tuilesUsed[index] = true;
                cout << "Tuile index : " << index << " est utilisée" << endl;
                cout << "Cpt : " << cpt << endl;
                threads[index] = thread(threadPoolLauncher, ref(finalPlateau), plateau, tuileIndex, tuilesUsed,
                                        ref(resolved));
            tuilesUsed[index] = false;
//            }
            plateau.popTuile();
            index++;
        }
    }
    for(int i = 0; i < nbTuiles; i++) {
        if(threads[i].joinable()) {
            threads[i].join();
        }
    }
    return false;
}

void threadPoolLauncher(Plateau& finalPlateau, Plateau plateau, int tuileIndex, vector<bool> tuilesUsed, bool& resolved) {
    cpt++;
    if(resolved) {
        cpt--;
        return;
    } else {
        Plateau plateauX = plateau;
        if(threadsRecursiveResolver(finalPlateau, plateau, tuileIndex + 1, std::move(tuilesUsed), resolved)) {
            cpt--;
            return;
        }
    }
    cpt--;
}

bool threadsRecursiveResolver(Plateau& finalPlateau, Plateau plateau, int tuileIndex, vector<bool> tuilesUsed, bool& resolved) {
    if(resolved) {
        return false;
    }
    if (tuileIndex == plateau.getTotalRows() * plateau.getTotalColumns()) {
        finalPlateau = plateau;
        resolved = true;
        return true;
    }

    for (int i = 0; i < plateau.getListTuiles().size(); i++) {
        if (!plateau.isTuileUsed(tuilesUsed, i)) {
            plateau.pushTuile(i);

            if (plateau.verifyTuile()) {
                tuilesUsed[i] = true;
                if (threadsRecursiveResolver(finalPlateau, plateau, tuileIndex + 1, tuilesUsed, resolved)) {
                    return true;
                }
                tuilesUsed[i] = false;
            }
            plateau.popTuile();
        }
    }
    return false;
}