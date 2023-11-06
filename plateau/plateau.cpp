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
//    this->tuilesUtilisees = vector<bool>(listeTuiles_.size(), false);
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

int Plateau::getTotalRows() {
    return this->totalRows_;
}

int Plateau::getTotalColumns() {
    return this->totalColumns_;
}

Tuile Plateau::getCurrentTuile() {
    return this->currentTuile_;
}

vector<Tuile> Plateau::getListeTuiles() {
    return this->listeTuiles_;
}

bool Plateau::isTuileUtilisee(vector<bool> tuilesUtilisees, int index) {
    return tuilesUtilisees[index];
}
void Plateau::pushTuile(int index) {
    if((currentRow_ == 0 && currentColumn_ == 0) && (nextRow_ == 0 && nextColumn_ == 0)) {
        bordureCouleur = this->listeTuiles_[index].getCouleurHaut();
    }
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

void Plateau::pushTuile(vector<Tuile> listeTuiles, int index) {
    currentColumn_ = nextColumn_;
    currentRow_ = nextRow_;

//    cout << "index : " << index << endl;
//    cout << "currentRow : " << currentRow_ << endl;
//    cout << "currentColumn : " << currentColumn_ << endl;

    this->plateau_[this->currentRow_][this->currentColumn_] = listeTuiles[index];
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

void Plateau::popTuile() {
    this->nextRow_ = this->currentRow_;
    this->nextColumn_ = this->currentColumn_;

    this->plateau_[this->currentRow_][this->currentColumn_] = this->defaultTuile_;

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
//        cout << "MonAngle" << verifyTuileForAngle() << endl;
//        cout << "MaBordure" << verifyCouleursBordure() << endl;
        isBonne = verifyTuileForAngle() && verifyCouleursBordure();
//        cout << "isBonne : " << isBonne << endl;
    }
    // Si c'est une tuile qui est sur la bordure
    else if (r == 0 || r == totalRows_ - 1 || c == 0 || c == totalColumns_ - 1) {
//        cout << "Bordure" << endl;
        isBonne = verifyCouleursBordure();
    }
//    cout << "Voisins :" << verifyCouleursVoisins() << endl;
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
        return (this->currentTuile_.getCouleurHaut() == this->currentTuile_.getCouleurDroite());
    } else if (this->currentRow_ == (this->totalRows_ - 1) && this->currentColumn_ == 0) {
        // Angle bas gauche
//        cout << "Angle bas gauche" << endl;
        return (this->currentTuile_.getCouleurGauche() == this->currentTuile_.getCouleurBas());
    } else if (this->currentRow_ == (this->totalRows_ - 1) && this->currentColumn_ == (this->totalColumns_ - 1)) {
        // Angle bas droit
//        cout << "Angle bas droit" << endl;
        return (this->currentTuile_.getCouleurBas() == this->currentTuile_.getCouleurDroite());
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
//        cout << bordureCouleur << endl;
        return (this->currentTuile_.getCouleurHaut() == this->bordureCouleur);
    } else if (c == 0) {
        // Si c'est une tuile sur la bordure de gauche
//        cout << this->currentTuile_.getCouleurGauche() << endl;
//        cout << this->bordureCouleur << endl;
        return (this->currentTuile_.getCouleurGauche() == this->bordureCouleur);
    } else if (r == this->totalRows_ - 1) {
        // Si c'est une tuile sur la bordure du bas
        return (this->currentTuile_.getCouleurBas() == this->bordureCouleur);
    } else if (c == this->totalColumns_ - 1) {
        // Si c'est une tuile sur la bordure de droite
        return (this->currentTuile_.getCouleurDroite() == this->bordureCouleur);
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
//        cout << "Angle de la mort qui tue" << endl;
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
        tuileDroite = defaultTuile_;
        tuileBas = defaultTuile_;
    } else if (r == totalRows_ - 1) {
//        cout << "Tuile du bas" << endl;
        tuileGauche = plateau_[r][c - 1];
        tuileHaut = plateau_[r - 1][c];
        tuileDroite = defaultTuile_;
        tuileBas = defaultTuile_;
    } else if ((0 < r < totalRows_ - 1) && (0 < c < totalColumns_ - 1)) {
//        cout << "Tuile du milieu" << endl;
        tuileGauche = plateau_[r][c - 1];
        tuileHaut = plateau_[r - 1][c];
        tuileDroite = this->defaultTuile_;
        tuileBas = this->defaultTuile_;
    } else if (c == 0) {
//        cout << "Tuile de gauche" << endl;
        tuileGauche = defaultTuile_;
        tuileHaut = plateau_[r - 1][c];
        tuileDroite = defaultTuile_;
        tuileBas = defaultTuile_;
    } else if (c == totalColumns_ - 1) {
//        cout << "Tuile de droite" << endl;
        tuileGauche = plateau_[r][c - 1];
        tuileHaut = plateau_[r - 1][c];
        tuileDroite = defaultTuile_;
        tuileBas = defaultTuile_;
    }

    // Vérifier les que les couleurs de la tuile actuelle sont bonnes en fonction des couleurs de ses voisins
    isBonne = ((tuileGauche.isTuileVide()) || (tuileGauche.getCouleurDroite() == currentTuile_.getCouleurGauche())) &&
              ((tuileHaut.isTuileVide()) || (tuileHaut.getCouleurBas() == currentTuile_.getCouleurHaut())) &&
              ((tuileDroite.isTuileVide()) || (tuileDroite.getCouleurGauche() == currentTuile_.getCouleurDroite())) &&
              ((tuileBas.isTuileVide()) || (tuileBas.getCouleurHaut() == currentTuile_.getCouleurBas()));
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
        return (currentTuile_.getCouleurHaut() == plateau_[currentRow_ - 1][currentColumn_].getCouleurBas());
    } else if (currentRow_ == (totalRows_ - 1) && currentColumn_ == (totalColumns_ - 1)) {
        // Angle bas droit
        return (currentTuile_.getCouleurGauche() == plateau_[currentRow_][currentColumn_ - 1].getCouleurDroite()) &&
               (currentTuile_.getCouleurHaut() == plateau_[currentRow_ - 1][currentColumn_].getCouleurBas());
    }
    cout << "Erreur dans la fonction verifyCouleursAngles()" << endl;
    return false;
}

bool Plateau::isRemplit() {
    if(currentRow_ == totalRows_-1 && currentColumn_ == totalColumns_-1) {
        cout << "currentRow_ : " << currentRow_ << endl;
        cout << "currentColumn_ : " << currentColumn_ << endl;
    }
    return (this->currentRow_ == this->totalRows_ - 1) && (this->currentColumn_ == this->totalColumns_ - 1);
}

vector<vector<Tuile>> Plateau::getPlateau() {
    return this->plateau_;
}