#include "tuile.h"
#include "iostream"

Tuile::Tuile() {
    this->couleurANSIGauche = couleursANSI['N'];
    this->couleurANSIHaut = couleursANSI['N'];
    this->couleurANSIDroite = couleursANSI['N'];
    this->couleurANSIBas = couleursANSI['N'];

    this->placement_[0] = 0;
    this->placement_[1] = 0;
}

Tuile::Tuile(char couleurGauche, char couleurHaut, char couleurDroite, char couleurBas) {
    this->couleurGauche = couleurGauche;
    this->couleurHaut = couleurHaut;
    this->couleurDroite = couleurDroite;
    this->couleurBas = couleurBas;

    this->couleurANSIGauche = couleursANSI[couleurGauche];
    this->couleurANSIHaut = couleursANSI[couleurHaut];
    this->couleurANSIDroite = couleursANSI[couleurDroite];
    this->couleurANSIBas = couleursANSI[couleurBas];
}

Tuile::Tuile(char couleurGauche, char couleurHaut, char couleurDroite, char couleurBas, int row, int column) {
    this->couleurGauche = couleurGauche;
    this->couleurHaut = couleurHaut;
    this->couleurDroite = couleurDroite;
    this->couleurBas = couleurBas;

    this->couleurANSIGauche = couleursANSI[couleurGauche];
    this->couleurANSIHaut = couleursANSI[couleurHaut];
    this->couleurANSIDroite = couleursANSI[couleurDroite];
    this->couleurANSIBas = couleursANSI[couleurBas];

    this->placement_[0] = row;
    this->placement_[1] = column;
}

void Tuile::afficher() {
    afficherLigneHaut();
    cout << endl;
    afficherLigneMilieu();
    cout << endl;
    afficherLigneBas();
    cout << endl;
}

void Tuile::afficherLigneHaut() {
    cout << this-> couleursANSI['N'] << "   ";
    cout << this->couleurANSIHaut << "███" << couleursANSI['N'];
    cout << this-> couleursANSI['N'] << "   ";
}

void Tuile::afficherLigneMilieu() {
    cout << this->couleurANSIGauche << "███" << couleursANSI['N'];
    cout << this-> couleursANSI['N'] << "   ";
    cout << this->couleurANSIDroite << "███" << couleursANSI['N'];
}

void Tuile::afficherLigneBas() {
    cout << this-> couleursANSI['N'] << "   ";
    cout << this->couleurANSIBas << "███" << couleursANSI['N'];
    cout << this-> couleursANSI['N'] << "   ";
};

vector<string> Tuile::getCouleurs() {
    vector<string> couleursTuile;
    couleursTuile.push_back(this->couleurANSIGauche);
    couleursTuile.push_back(this->couleurANSIHaut);
    couleursTuile.push_back(this->couleurANSIDroite);
    couleursTuile.push_back(this->couleurANSIBas);
    return couleursTuile;
}

char Tuile::getCouleurGauche() {
    return this->couleurGauche;
}

char Tuile::getCouleurHaut() {
    return this->couleurHaut;
}

char Tuile::getCouleurDroite() {
    return this->couleurDroite;
}

char Tuile::getCouleurBas() {
    return this->couleurBas;
}

vector<int> Tuile::getPlacement() {
    return this->placement_;
}