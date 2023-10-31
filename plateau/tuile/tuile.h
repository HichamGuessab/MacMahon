#ifndef MACMAHON_TUILE_H
#define MACMAHON_TUILE_H

#include "string"
#include <map>

using namespace std;

class Tuile {
public:
    Tuile();
    Tuile(char gauche, char haut, char droite, char bas);
    Tuile(char couleurGauche, char couleurHaut, char couleurDroite, char couleurBas, int row, int column);

    vector<string> getCouleurs();

    char getCouleurGauche();
    char getCouleurHaut();
    char getCouleurDroite();
    char getCouleurBas();

    vector<int> getPlacement();

    void afficher();
    void afficherLigneHaut();
    void afficherLigneMilieu();
    void afficherLigneBas();

    bool isTuileVide();

private:
    char couleurGauche;
    char couleurHaut;
    char couleurDroite;
    char couleurBas;

    string couleurANSIGauche;
    string couleurANSIHaut;
    string couleurANSIDroite;
    string couleurANSIBas;
    map<char, string> couleursANSI = {
            {'N', "\x1B[0m"},
            {'R', "\x1B[31m"},
            {'G', "\x1B[32m"},
            {'B', "\x1B[34m"}
    };
};

#endif // MACMAHON_TUILE_H
