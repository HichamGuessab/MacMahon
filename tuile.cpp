#include "tuile.h"
#include "iostream"

Tuile::Tuile() {
    this->couleurGauche = couleurs['N'];
    this->couleurHaut = couleurs['N'];
    this->couleurDroite = couleurs['N'];
    this->couleurBas = couleurs['N'];
}

Tuile::Tuile(char couleurGauche, char couleurHaut, char couleurDroite, char couleurBas) {
    this->couleurGauche = couleurs[couleurGauche];
    this->couleurHaut = couleurs[couleurHaut];
    this->couleurDroite = couleurs[couleurDroite];
    this->couleurBas = couleurs[couleurBas];
}

void Tuile::afficher() {
    afficherLigneHaut();
    cout << endl;
    afficherLigneMilieu();
    cout << endl;
    afficherLigneBas();
}

void Tuile::afficherLigneHaut() {
    cout << this-> couleurs['N'] <<"   ";
    cout << this->couleurHaut << "███" << couleurs['N'];
    cout << this-> couleurs['N'] <<"   ";
}

void Tuile::afficherLigneMilieu() {
    cout << this->couleurGauche << "███" << couleurs['N'];
    cout << this-> couleurs['N'] <<"   ";
    cout << this->couleurDroite << "███" << couleurs['N'];
}

void Tuile::afficherLigneBas() {
    cout << this-> couleurs['N'] <<"   ";
    cout << this->couleurBas << "███" << couleurs['N'];
    cout << this-> couleurs['N'] <<"   ";
};

vector<string> Tuile::getCouleurs() {
vector<string> couleursTuile;
    couleursTuile.push_back(this->couleurGauche);
    couleursTuile.push_back(this->couleurHaut);
    couleursTuile.push_back(this->couleurDroite);
    couleursTuile.push_back(this->couleurBas);
    return couleursTuile;
}