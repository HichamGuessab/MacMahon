#include "plateau.h"
#include "iostream"

using namespace std;

Plateau::Plateau(vector<string> fichier) {
    this->fichier_ = fichier;
    this->rows_ = fichier[0][0] - '0';
    this->columns_ = fichier[0][2] - '0';
    this->plateau_ = vector<vector<Tuile>>();
}

void Plateau::remplir() {
    vector<Tuile> lignesTuile = vector<Tuile>();
    for (int i = 1; i < (this->rows_ * this->columns_) + 1; i++) {
        Tuile tuile = Tuile(this->fichier_[i][0], this->fichier_[i][2], this->fichier_[i][4], this->fichier_[i][6]);
        lignesTuile.push_back(tuile);
        if (i % this->columns_ == 0) {
            this->plateau_.push_back(lignesTuile);
            lignesTuile.clear();
        }
    }
}

void Plateau::afficher() {
    for (int i = 0; i < this->rows_; i++) {
        for (int j = 0; j < this->columns_; j++) {
            Tuile currentTuile = this->plateau_[i][j];
            currentTuile.afficherLigneHaut();
            cout << "  ";
        }
        cout << endl;
        for (int j = 0; j < this->columns_; j++) {
            Tuile currentTuile = this->plateau_[i][j];
            currentTuile.afficherLigneMilieu();
            cout << "  ";
        }
        cout << endl;
        for (int j = 0; j < this->columns_; j++) {
            Tuile currentTuile = this->plateau_[i][j];
            currentTuile.afficherLigneBas();
            cout << "  ";
        }
        cout << endl;
        cout << endl;
    }
}
