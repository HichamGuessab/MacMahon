#include "tuile.h"
#include "iostream"

Tuile::Tuile() {
    this->couleurGauche = 'N';
    this->couleurHaut = 'N';
    this->couleurDroite = 'N';
    this->couleurBas = 'N';

    this->couleurANSIGauche = couleursANSI['N'];
    this->couleurANSIHaut = couleursANSI['N'];
    this->couleurANSIDroite = couleursANSI['N'];
    this->couleurANSIBas = couleursANSI['N'];
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
}

void Tuile::afficher() {
    afficherLigneHaut();
    cout << endl;
    afficherLigneMilieu();
    cout << endl;
    afficherLigneBas();
    cout << endl << endl;
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

bool Tuile::isTuileVide() {
    return this->couleurGauche == 'N' &&
           this->couleurHaut == 'N' &&
           this->couleurDroite == 'N' &&
           this->couleurBas == 'N';
}