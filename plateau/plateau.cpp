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
        cout << i << endl;
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

//    cout << "index : " << index << endl;
//    cout << "currentRow : " << currentRow_ << endl;
//    cout << "currentColumn : " << currentColumn_ << endl;

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
        this->nextColumn_ = currentColumn_ + 1;
        this->nextRow_ = currentRow_;
    }
//    cout << "nextRow : " << nextRow_ << endl;
//    cout << "nextColumn : " << nextColumn_ << endl;
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
        this->currentColumn_ = this->totalColumns_ - 1;
        this->currentRow_--;
    } else {
        this->currentColumn_--;
    }

    this->currentTuile_ = this->plateau_[this->currentRow_][this->currentColumn_];
}

bool Plateau::verifyTuile() {
    bool isBonne = true;

    int r = this->currentRow_;
    int c = this->currentColumn_;

    // Si c'est la première Tuile
    if ((this->currentRow_ == 0 && this->currentColumn_ == 0)) {
        this->bordureCouleur = this->currentTuile_.getCouleurHaut();
//        cout << "bordureCouleur" << bordureCouleur << endl;
    }
    // Si c'est une tuile des angles
    if ((r == 0 || r == totalRows_ - 1) && (c == 0 || c == totalColumns_ - 1)) {
//        cout << "Angle" << endl;
        isBonne = verifyTuileForAngle();
    }
    // Si c'est une tuile qui est sur la bordure (y compris les angles)
    if (r == 0 || r == totalRows_ - 1 || c == 0 || c == totalColumns_ - 1) {
//        cout << "Bordure" << endl;
        isBonne = verifyCouleursBordure();
    }
    return isBonne && verifyCouleursVoisins();
}

bool Plateau::verifyTuileForAngle() {
    // Vérifier en fonction de sa position si les couleurs de ses angles sont bonnes
    if (this->currentRow_ == 0 && this->currentColumn_ == 0) {
        // Angle haut gauche
//        cout << "Angle Haut gauche" << endl;
        // Cet angle est seulement bon si la couleur du haut est la même que la couleur de gauche
        return this->currentTuile_.getCouleurGauche() == this->currentTuile_.getCouleurHaut();
    } else if (this->currentRow_ == 0 && this->currentColumn_ == this->totalColumns_ - 1) {
        // Angle haut droit
//        cout << "Angle haut droit" << endl;
        return (this->currentTuile_.getCouleurHaut() == this->currentTuile_.getCouleurDroite()) &&
               (this->currentTuile_.getCouleurGauche() == this->plateau_[this->currentRow_][this->currentColumn_ - 1].getCouleurDroite());
    } else if (this->currentRow_ == (this->totalRows_ - 1) && this->currentColumn_ == 0) {
        // Angle bas gauche
//        cout << "Angle bas gauche" << endl;
        return (this->currentTuile_.getCouleurGauche() == this->currentTuile_.getCouleurBas()) &&
               (this->currentTuile_.getCouleurHaut() == this->plateau_[this->currentRow_ - 1][this->currentColumn_].getCouleurBas()) &&
               (this->currentTuile_.getCouleurDroite() == this->plateau_[this->currentRow_][this->currentColumn_ + 1].getCouleurBas());
    } else if (this->currentRow_ == (this->totalRows_ - 1) && this->currentColumn_ == (this->totalColumns_ - 1)) {
        // Angle bas droit
//        cout << "Angle bas droit" << endl;
        return (this->currentTuile_.getCouleurBas() == this->currentTuile_.getCouleurDroite()) &&
               (this->currentTuile_.getCouleurGauche() == this->plateau_[this->currentRow_][this->currentColumn_ - 1].getCouleurDroite()) &&
               (this->currentTuile_.getCouleurHaut() == this->plateau_[this->currentRow_ - 1][this->currentColumn_].getCouleurBas());
    }
    cout << "Erreur dans la fonction verifyTuileForAngle()" << endl;
    return true;
}

bool Plateau::verifyCouleursBordure() {
    int r = this->currentRow_;
    int c = this->currentColumn_;

//    cout << "r :" << r << endl;
//    cout << "c :" << c << endl;

    if (r == 0) {
        // Si c'est une tuile sur la bordure du haut
        return this->currentTuile_.getCouleurHaut() == this->bordureCouleur;
    } else if (c == 0) {
        // Si c'est une tuile sur la bordure de gauche
        return this->currentTuile_.getCouleurGauche() == this->bordureCouleur;
    } else if (r == this->totalRows_ - 1) {
        // Si c'est une tuile sur la bordure du bas
        return this->currentTuile_.getCouleurBas() == this->bordureCouleur;
    } else if (c == this->totalColumns_ - 1) {
        // Si c'est une tuile sur la bordure de droite
        return this->currentTuile_.getCouleurDroite() == this->bordureCouleur;
    }
    return true;
}

bool Plateau::verifyCouleursVoisins() {
//    cout << "verifyCouleursVoisins()" << endl;
    bool isBonne = true;

    int r = currentRow_;
    int c = currentColumn_;

    // Vérification des couleurs si c'est un angle
    if ((r == 0 || r == totalRows_ - 1) && (c == 0 || c == totalColumns_ - 1)) {
        return verifyCouleursAngles();
    }

    // Assignation des tuiles voisines en fonction de la position de la tuile actuelle
    Tuile tuileGauche;
    Tuile tuileHaut;
    Tuile tuileDroite;
    Tuile tuileBas;

    if (r == 0) {
//        cout << "Tuile du haut" << endl;
        tuileGauche = plateau_[r][c - 1];
        tuileHaut = defaultTuile_;
        tuileDroite = plateau_[r][c + 1];
        tuileBas = plateau_[r + 1][c];
    } else if (r == totalRows_ - 1) {
//        cout << "Tuile du bas" << endl;
        tuileGauche = plateau_[r][c - 1];
        tuileHaut = plateau_[r - 1][c];
        tuileDroite = plateau_[r][c + 1];
        tuileBas = defaultTuile_;
    } else if ((0 < r < totalRows_ - 1) && (0 < c < totalColumns_ - 1)) {
//        cout << "Tuile du milieu" << endl;
        tuileGauche = plateau_[r][c - 1];
        tuileHaut = plateau_[r - 1][c];
        tuileDroite = plateau_[r][c + 1];
        tuileBas = plateau_[r + 1][c];
    } else if (c == 0) {
//        cout << "Tuile de gauche" << endl;
        tuileGauche = defaultTuile_;
        tuileHaut = plateau_[r - 1][c];
        tuileDroite = plateau_[r][c + 1];
        tuileBas = defaultTuile_;
    } else if (c == totalColumns_ - 1) {
//        cout << "Tuile de droite" << endl;
        tuileGauche = plateau_[r][c - 1];
        tuileHaut = plateau_[r - 1][c];
        tuileDroite = defaultTuile_;
        tuileBas = defaultTuile_;
    }

    // Vérifier les que les couleurs de la tuile actuelle sont bonnes en fonction des couleurs de ses voisins
    isBonne = ((tuileGauche.isTuileVide()) || (tuileGauche.getCouleurGauche() == currentTuile_.getCouleurGauche())) &&
              ((tuileHaut.isTuileVide()) || (tuileHaut.getCouleurHaut() == currentTuile_.getCouleurHaut())) &&
              ((tuileDroite.isTuileVide()) || (tuileDroite.getCouleurDroite() == currentTuile_.getCouleurDroite())) &&
              ((tuileBas.isTuileVide()) || (tuileBas.getCouleurBas() == currentTuile_.getCouleurBas()));
    return isBonne;
}

bool Plateau::verifyCouleursAngles() {
    if (currentRow_ == 0 && currentColumn_ == 0) {
        // Angle haut gauche
        return currentTuile_.getCouleurGauche() == currentTuile_.getCouleurHaut();
    } else if (currentRow_ == 0 && currentColumn_ == totalColumns_ - 1) {
        // Angle haut droit
        return currentTuile_.getCouleurGauche() == plateau_[currentRow_][currentColumn_ - 1].getCouleurDroite();
    } else if (currentRow_ == (totalRows_ - 1) && currentColumn_ == 0) {
        // Angle bas gauche
        return (currentTuile_.getCouleurHaut() == plateau_[currentRow_ - 1][currentColumn_].getCouleurBas()) &&
               (currentTuile_.getCouleurDroite() == plateau_[currentRow_][currentColumn_ + 1].getCouleurBas());
    } else if (currentRow_ == (totalRows_ - 1) && currentColumn_ == (totalColumns_ - 1)) {
        // Angle bas droit
        return (currentTuile_.getCouleurGauche() == plateau_[currentRow_][currentColumn_ - 1].getCouleurDroite()) &&
               (currentTuile_.getCouleurHaut() == plateau_[currentRow_ - 1][currentColumn_].getCouleurBas());
    }
    cout << "Erreur dans la fonction verifyCouleursAngles()" << endl;
    return false;
}