#include "plateau.h"
#include "iostream"

using namespace std;

Plateau::Plateau(vector<string> file) {
    // Le - '0' permet de convertir le char en int
    this->totalRows_ = file[0][0] - '0';
    this->totalColumns_ = file[0][2] - '0';

    this->currentRow_ = 0;
    this->currentColumn_ = 0;

    this->nextRow_ = 0;
    this->nextColumn_ = 0;

    this->listTuiles_ = vector<Tuile>();

    this->plateau_ = vector<vector<Tuile>>(this->totalRows_, vector<Tuile>(this->totalColumns_));
    fillListTuiles(file);
}

void Plateau::fillListTuiles(vector<string> file) {
    for (int i = 1; i < (this->totalRows_ * this->totalColumns_) + 1; i++) {
        Tuile tuile = Tuile(file[i][0], file[i][2], file[i][4], file[i][6]);
        this->listTuiles_.push_back(tuile);
    }
//    this->tuilesUtilisees = vector<bool>(listTuiles_.size(), false);
}

void Plateau::displayListTuiles() {
    int nbTuiles = 0;
    for (int i = 0; i < this->listTuiles_.size(); i++) {
        this->listTuiles_[i].display();
        cout << i << endl;
        nbTuiles++;
    }
    cout << "Nombre de tuiles : " << nbTuiles << endl;
}

void Plateau::display() {
    for (int i = 0; i < this->totalRows_; i++) {
        for (int j = 0; j < this->totalColumns_; j++) {
            this->plateau_[i][j].displayTopLine();
            cout << "  ";
        }
        cout << endl;
        for (int j = 0; j < this->totalColumns_; j++) {
            this->plateau_[i][j].displayMiddleLine();
            cout << "  ";
        }
        cout << endl;
        for (int j = 0; j < this->totalColumns_; j++) {
            this->plateau_[i][j].displayBottomLine();
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

vector<Tuile> Plateau::getListTuiles() {
    return this->listTuiles_;
}

bool Plateau::isTuileUsed(vector<bool> tuilesUsed, int index) {
    return tuilesUsed[index];
}
void Plateau::pushTuile(int index) {
    if((currentRow_ == 0 && currentColumn_ == 0) && (nextRow_ == 0 && nextColumn_ == 0)) {
        borderColor = this->listTuiles_[index].getTopColor();
    }
    currentColumn_ = nextColumn_;
    currentRow_ = nextRow_;

//    cout << "index : " << index << endl;
//    cout << "currentRow : " << currentRow_ << endl;
//    cout << "currentColumn : " << currentColumn_ << endl;

    this->plateau_[this->currentRow_][this->currentColumn_] = this->listTuiles_[index];
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
    bool isGood = true;

    int r = this->currentRow_;
    int c = this->currentColumn_;

    // Si c'est la première Tuile
    if ((this->currentRow_ == 0 && this->currentColumn_ == 0)) {
        this->borderColor = this->currentTuile_.getTopColor();
//        cout << "borderColor" << borderColor << endl;
    }
    // Si c'est une tuile des angles
    if ((r == 0 || r == totalRows_ - 1) && (c == 0 || c == totalColumns_ - 1)) {
//        cout << "Angle" << endl;
//        cout << "MonAngle" << verifyTuileForCorner() << endl;
//        cout << "MaBordure" << verifyBordersColors() << endl;
        isGood = verifyTuileForCorner() && verifyBordersColors();
//        cout << "isGood : " << isGood << endl;
    }
    // Si c'est une tuile qui est sur la bordure
    else if (r == 0 || r == totalRows_ - 1 || c == 0 || c == totalColumns_ - 1) {
//        cout << "Bordure" << endl;
        isGood = verifyBordersColors();
    }
//    cout << "Voisins :" << verifyNeighborsColors() << endl;
    return isGood && verifyNeighborsColors();
}

bool Plateau::verifyTuileForCorner() {
    // Vérifier en fonction de sa position si les couleurs de ses angles sont bonnes
    if (this->currentRow_ == 0 && this->currentColumn_ == 0) {
        // Angle haut gauche
//        cout << "Angle Haut gauche" << endl;
        // Cet angle est seulement bon si la couleur du haut est la même que la couleur de gauche
        return this->currentTuile_.getLeftColor() == this->currentTuile_.getTopColor();
    } else if (this->currentRow_ == 0 && this->currentColumn_ == this->totalColumns_ - 1) {
        // Angle haut droit
//        cout << "Angle haut droit" << endl;
        return (this->currentTuile_.getTopColor() == this->currentTuile_.getRightColor());
    } else if (this->currentRow_ == (this->totalRows_ - 1) && this->currentColumn_ == 0) {
        // Angle bas gauche
//        cout << "Angle bas gauche" << endl;
        return (this->currentTuile_.getLeftColor() == this->currentTuile_.getBottomColor());
    } else if (this->currentRow_ == (this->totalRows_ - 1) && this->currentColumn_ == (this->totalColumns_ - 1)) {
        // Angle bas droit
//        cout << "Angle bas droit" << endl;
        return (this->currentTuile_.getBottomColor() == this->currentTuile_.getRightColor());
    }
    cout << "Erreur dans la fonction verifyTuileForCorner()" << endl;
    return true;
}

bool Plateau::verifyBordersColors() {
    int r = this->currentRow_;
    int c = this->currentColumn_;

//    cout << "r :" << r << endl;
//    cout << "c :" << c << endl;

    if (r == 0) {
        // Si c'est une tuile sur la bordure du haut
//        cout << borderColor << endl;
        return (this->currentTuile_.getTopColor() == this->borderColor);
    } else if (c == 0) {
        // Si c'est une tuile sur la bordure de gauche
//        cout << this->currentTuile_.getLeftColor() << endl;
//        cout << this->borderColor << endl;
        return (this->currentTuile_.getLeftColor() == this->borderColor);
    } else if (r == this->totalRows_ - 1) {
        // Si c'est une tuile sur la bordure du bas
        return (this->currentTuile_.getBottomColor() == this->borderColor);
    } else if (c == this->totalColumns_ - 1) {
        // Si c'est une tuile sur la bordure de droite
        return (this->currentTuile_.getRightColor() == this->borderColor);
    }
    return true;
}

bool Plateau::verifyNeighborsColors() {
//    cout << "verifyNeighborsColors()" << endl;
    bool isGood = true;

    int r = currentRow_;
    int c = currentColumn_;

    // Vérification des couleurs si c'est un angle
    if ((r == 0 || r == totalRows_ - 1) && (c == 0 || c == totalColumns_ - 1)) {
//        cout << "Angle de la mort qui tue" << endl;
        return verifyCornersColors();
    }

    // Assignation des tuiles voisines en fonction de la position de la tuile actuelle
    Tuile leftTuile;
    Tuile topTuile;
    Tuile rightTuile;
    Tuile bottomTuile;

    if (r == 0) {
//        cout << "Tuile du haut" << endl;
        leftTuile = plateau_[r][c - 1];
        topTuile = defaultTuile_;
        rightTuile = defaultTuile_;
        bottomTuile = defaultTuile_;
    } else if (r == totalRows_ - 1) {
//        cout << "Tuile du bas" << endl;
        leftTuile = plateau_[r][c - 1];
        topTuile = plateau_[r - 1][c];
        rightTuile = defaultTuile_;
        bottomTuile = defaultTuile_;
    } else if (((r > 0) && (r < (totalRows_ - 1))) && ((c > 0) && (c < (totalColumns_ - 1)))) {
//        cout << "Tuile du milieu" << endl;
        leftTuile = plateau_[r][c - 1];
        topTuile = plateau_[r - 1][c];
        rightTuile = this->defaultTuile_;
        bottomTuile = this->defaultTuile_;
    } else if (c == 0) {
//        cout << "Tuile de gauche" << endl;
        leftTuile = defaultTuile_;
        topTuile = plateau_[r - 1][c];
        rightTuile = defaultTuile_;
        bottomTuile = defaultTuile_;
    } else if (c == totalColumns_ - 1) {
//        cout << "Tuile de droite" << endl;
        leftTuile = plateau_[r][c - 1];
        topTuile = plateau_[r - 1][c];
        rightTuile = defaultTuile_;
        bottomTuile = defaultTuile_;
    }

    // Vérifier les que les couleurs de la tuile actuelle sont bonnes en fonction des couleurs de ses voisins
    isGood = ((leftTuile.isEmpty()) || (leftTuile.getRightColor() == currentTuile_.getLeftColor())) &&
             ((topTuile.isEmpty()) || (topTuile.getBottomColor() == currentTuile_.getTopColor())) &&
             ((rightTuile.isEmpty()) || (rightTuile.getLeftColor() == currentTuile_.getRightColor())) &&
             ((bottomTuile.isEmpty()) || (bottomTuile.getTopColor() == currentTuile_.getBottomColor()));
    return isGood;
}

bool Plateau::verifyCornersColors() {
    if (currentRow_ == 0 && currentColumn_ == 0) {
        // Angle haut gauche
        return currentTuile_.getLeftColor() == currentTuile_.getTopColor();
    } else if (currentRow_ == 0 && currentColumn_ == totalColumns_ - 1) {
        // Angle haut droit
        return currentTuile_.getLeftColor() == plateau_[currentRow_][currentColumn_ - 1].getRightColor();
    } else if (currentRow_ == (totalRows_ - 1) && currentColumn_ == 0) {
        // Angle bas gauche
        return (currentTuile_.getTopColor() == plateau_[currentRow_ - 1][currentColumn_].getBottomColor());
    } else if (currentRow_ == (totalRows_ - 1) && currentColumn_ == (totalColumns_ - 1)) {
        // Angle bas droit
        return (currentTuile_.getLeftColor() == plateau_[currentRow_][currentColumn_ - 1].getRightColor()) &&
               (currentTuile_.getTopColor() == plateau_[currentRow_ - 1][currentColumn_].getBottomColor());
    }
    cout << "Erreur dans la fonction verifyCornersColors()" << endl;
    return false;
}

vector<vector<Tuile>> Plateau::getPlateau() {
    return this->plateau_;
}