#include "tuile.h"
#include "iostream"

Tuile::Tuile(char couleurGauche, char couleurHaut, char couleurDroite, char couleurBas) {
    // Pour chaque couleur, on associe son ANSI
    this->couleurGauche = couleurs[couleurGauche];
    this->couleurHaut = couleurs[couleurHaut];
    this->couleurDroite = couleurs[couleurDroite];
    this->couleurBas = couleurs[couleurBas];
}

void Tuile::afficher() {
    // On remet la couleur par défaut si la couleur donné en argument n'est pas bonne
    cout << this-> couleurs['N'] << "██";
    cout << this->couleurHaut << "██" << couleurs['N'];
    cout << this-> couleurs['N'] << "██" << endl;
    cout << this->couleurGauche << "██" << couleurs['N'];
    cout << this-> couleurs['N'] << "██";
    cout << this->couleurDroite << "██" << couleurs['N'] << endl;
    cout << this-> couleurs['N'] << "██";
    cout << this->couleurBas << "██" << couleurs['N'];
    cout << this-> couleurs['N'] << "██" << endl;
}

