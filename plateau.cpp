#include "plateau.h"
#include "iostream"

using namespace std;

Plateau::Plateau(vector<string> fichier) {
    this->fichier_ = fichier;
    this->rows_ = fichier[0][0] - '0';
    this->columns_ = fichier[0][2] - '0';
    this->plateau_ = vector<vector<Tuile>>(this->rows_, vector<Tuile>());
}

void Plateau::remplir() {
    for (int i = 1; i < this->rows_ + 1; i++) {
        for (int j = 0; j < this->columns_; j++) {
            this->plateau_[i - 1].emplace_back('G', 'R', 'B', 'R');
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
