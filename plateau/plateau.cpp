#include "plateau.h"
#include "iostream"

using namespace std;

Plateau::Plateau(vector<string> fichier) {
    // Le - '0' permet de convertir le char en int
    this->totalRows_ = fichier[0][0] - '0';
    this->totalColumns_ = fichier[0][2] - '0';

    this->currentRow_ = 0;
    this->currentColumn_ = 0;

    this->nextRow_ = 0;
    this->nextColumn_ = 0;

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

Tuile Plateau::getCurrentTuile() {
    return this->currentTuile_;
}

void Plateau::pushTuile(int index) {
    currentColumn_ = nextColumn_;
    currentRow_ = nextRow_;

    cout << "index : " << index << endl;
    cout << "currentRow : " << currentRow_ << endl;
    cout << "currentColumn : " << currentColumn_ << endl;

    this->plateau_[this->currentRow_][this->currentColumn_] = this->listeTuiles_[index];
    this->currentTuile_ = this->plateau_[this->currentRow_][this->currentColumn_];

    if ((this->currentColumn_ == this->totalColumns_ - 1) &&
        (this->currentRow_ == this->totalRows_ - 1)) {
        // Dernière tuile du plateau
        this->nextColumn_ = this->totalColumns_ - 1;
        this->nextRow_ = this->totalRows_ - 1;
    } else if ((this->currentColumn_ == this->totalColumns_ - 1) &&
               (this->currentRow_ < this->totalRows_ - 1)) {
        // Dernière colonne d'une ligne
        this->nextColumn_ = 0;
        this->nextRow_ = currentRow_ + 1;
    } else {
        cout << "here" << endl;
        this->nextColumn_ = currentColumn_ + 1;
        this->nextRow_ = currentRow_;
    }
    cout << "nextRow : " << nextRow_ << endl;
    cout << "nextColumn : " << nextColumn_ << endl;
}

void Plateau::popTuile(int row, int column) {
    this->nextRow_ = this->currentRow_;
    this->nextColumn_ = this->currentColumn_;

    this->plateau_[row][column] = this->defaultTuile_;

    // Mise à jour des coordonnées de la tuile actuelle
    if (this->currentRow_ == 0 && this->currentColumn_ == 0) {
        // Si c'est la première tuile
        this->currentColumn_ = 0;
        this->currentRow_ = 0;
    } else if (this->currentRow_ > 0 && this->currentColumn_ == 0) {
        // Si c'est une tuile sur la première colonne (sauf première ligne)
        this->currentColumn_ == this->totalColumns_ - 1;
        this->currentRow_--;
    } else {
        this->currentColumn_--;
    }

    this->currentTuile_ = this->plateau_[this->currentRow_][this->currentColumn_];
}