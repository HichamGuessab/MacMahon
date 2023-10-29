#ifndef MACMAHON_TUILE_H
#define MACMAHON_TUILE_H

#include "string"
#include <map>

using namespace std;

class Tuile {
public:
    Tuile();
    Tuile(char gauche, char haut, char droite, char bas);
    void afficher();
    void afficherLigneHaut();
    void afficherLigneMilieu();
    void afficherLigneBas();
    vector<string> getCouleurs();
private:
    string couleurGauche;
    string couleurHaut;
    string couleurDroite;
    string couleurBas;
    map<char, string> couleurs = {
            {'N', "\x1B[0m"},
            {'R', "\x1B[31m"},
            {'G', "\x1B[32m"},
            {'B', "\x1B[34m"}
    };
};

#endif // MACMAHON_TUILE_H
