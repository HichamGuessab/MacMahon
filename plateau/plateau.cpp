#include "plateau.h"
#include "iostream"

using namespace std;

Plateau::Plateau(vector<string> fichier) {
    // Le - '0' permet de convertir le char en int
    this->totalRows_ = fichier[0][0] - '0';
    this->totalColumns_ = fichier[0][2] - '0';
    this->currentRow_ = 0;
    this->currentColumn_ = 0;
    this->listeTuiles_ = vector<Tuile>();
    this->plateau_ = vector<vector<Tuile>>(this->totalRows_, vector<Tuile>(this->totalColumns_));
    remplirListeTuiles(fichier);
}

void Plateau::remplirListeTuiles(vector<string> fichier) {
    for (int i = 1; i < (this->totalRows_ * this->totalColumns_) + 1; i++) {
        Tuile tuile = Tuile(fichier[i][0], fichier[i][2], fichier[i][4], fichier[i][6]);
        this->listeTuiles_.push_back(tuile);
    }
}

void Plateau::afficherListeTuiles() {
    int nombre_tuile = 0;
    for (int i = 0; i < this->listeTuiles_.size(); i++) {
        this->listeTuiles_[i].afficher();
        nombre_tuile++;
    }
    cout << "Nombre de tuiles : " << nombre_tuile << endl;
}

void Plateau::afficher() {
    for (int i = 0; i < this->totalRows_; i++) {
        for (int j = 0; j < this->totalColumns_; j++) {
            this->plateau_[i][j].afficherLigneHaut();
            cout << "  ";
        }
        cout << endl;
        for (int j = 0; j < this->totalColumns_; j++) {
            this->plateau_[i][j].afficherLigneMilieu();
            cout << "  ";
        }
        cout << endl;
        for (int j = 0; j < this->totalColumns_; j++) {
            this->plateau_[i][j].afficherLigneBas();
            cout << "  ";
        }
        cout << endl;
        cout << endl;
    }
}

void Plateau::pushTuile(int index) {
    cout << "index : " << index << endl;
    cout << "currentRow : " << currentRow_ << endl;
    cout << "currentColumn : " << currentColumn_ << endl;
    this->plateau_[this->currentRow_][this->currentColumn_] = this->listeTuiles_[index];
    this->currentRow_++;
    if (this->currentRow_ == this->totalRows_) {
        this->currentRow_ = 0;
        this->currentColumn_++;
    }
}