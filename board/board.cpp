#include "board.h"
#include "iostream"

using namespace std;

Board::Board(vector<string> file) {
    // Le - '0' permet de convertir le char en int
    this->totalRows_ = file[0][0] - '0';
    this->totalColumns_ = file[0][2] - '0';

    this->currentRow_ = 0;
    this->currentColumn_ = 0;

    this->nextRow_ = 0;
    this->nextColumn_ = 0;

    this->listTiles_ = vector<Tile>();

    this->board_ = vector<vector<Tile>>(this->totalRows_, vector<Tile>(this->totalColumns_));
    fillListTiles(file);
}

void Board::fillListTiles(vector<string> file) {
    for (int i = 1; i < (this->totalRows_ * this->totalColumns_) + 1; i++) {
        Tile tile = Tile(file[i][0], file[i][2], file[i][4], file[i][6]);
        this->listTiles_.push_back(tile);
    }
//    this->tilesUtilisees = vector<bool>(listTiles_.size(), false);
}

void Board::displayListTiles() {
    int nbTiles = 0;
    for (int i = 0; i < this->listTiles_.size(); i++) {
        this->listTiles_[i].display();
        cout << i << endl;
        nbTiles++;
    }
    cout << "Nombre de tiles : " << nbTiles << endl;
}

void Board::display() {
    for (int i = 0; i < this->totalRows_; i++) {
        for (int j = 0; j < this->totalColumns_; j++) {
            this->board_[i][j].displayTopLine();
            cout << "  ";
        }
        cout << endl;
        for (int j = 0; j < this->totalColumns_; j++) {
            this->board_[i][j].displayMiddleLine();
            cout << "  ";
        }
        cout << endl;
        for (int j = 0; j < this->totalColumns_; j++) {
            this->board_[i][j].displayBottomLine();
            cout << "  ";
        }
        cout << endl;
        cout << endl;
    }
}

int Board::getTotalRows() {
    return this->totalRows_;
}

int Board::getTotalColumns() {
    return this->totalColumns_;
}

Tile Board::getCurrentTile() {
    return this->currentTile_;
}

vector<Tile> Board::getListTiles() {
    return this->listTiles_;
}

bool Board::isTileUsed(vector<bool> tilesUsed, int index) {
    return tilesUsed[index];
}
void Board::pushTile(int index) {
    if((currentRow_ == 0 && currentColumn_ == 0) && (nextRow_ == 0 && nextColumn_ == 0)) {
        borderColor = this->listTiles_[index].getTopColor();
    }
    currentColumn_ = nextColumn_;
    currentRow_ = nextRow_;

//    cout << "index : " << index << endl;
//    cout << "currentRow : " << currentRow_ << endl;
//    cout << "currentColumn : " << currentColumn_ << endl;

    this->board_[this->currentRow_][this->currentColumn_] = this->listTiles_[index];
    this->currentTile_ = this->board_[this->currentRow_][this->currentColumn_];

    if ((this->currentColumn_ == this->totalColumns_ - 1) &&
        (this->currentRow_ == this->totalRows_ - 1)) {
        // Dernière tile du board
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

void Board::popTile() {
    this->nextRow_ = this->currentRow_;
    this->nextColumn_ = this->currentColumn_;

    this->board_[this->currentRow_][this->currentColumn_] = this->defaultTile_;

    // Mise à jour des coordonnées de la tile actuelle
    if (this->currentRow_ == 0 && this->currentColumn_ == 0) {
        // Si c'est la première tile
        this->currentColumn_ = 0;
        this->currentRow_ = 0;
    } else if (this->currentRow_ > 0 && this->currentColumn_ == 0) {
        // Si c'est une tile sur la première colonne (sauf première ligne)
        this->currentColumn_ = this->totalColumns_ - 1;
        this->currentRow_--;
    } else {
        this->currentColumn_--;
    }

    this->currentTile_ = this->board_[this->currentRow_][this->currentColumn_];
}

bool Board::verifyTile() {
    bool isGood = true;

    int r = this->currentRow_;
    int c = this->currentColumn_;

    // Si c'est la première Tile
    if ((this->currentRow_ == 0 && this->currentColumn_ == 0)) {
        this->borderColor = this->currentTile_.getTopColor();
//        cout << "borderColor" << borderColor << endl;
    }
    // Si c'est une tile des angles
    if ((r == 0 || r == totalRows_ - 1) && (c == 0 || c == totalColumns_ - 1)) {
//        cout << "Angle" << endl;
//        cout << "MonAngle" << verifyTileForCorner() << endl;
//        cout << "MaBordure" << verifyBordersColors() << endl;
        isGood = verifyTileForCorner() && verifyBordersColors();
//        cout << "isGood : " << isGood << endl;
    }
    // Si c'est une tile qui est sur la bordure
    else if (r == 0 || r == totalRows_ - 1 || c == 0 || c == totalColumns_ - 1) {
//        cout << "Bordure" << endl;
        isGood = verifyBordersColors();
    }
//    cout << "Voisins :" << verifyNeighborsColors() << endl;
    return isGood && verifyNeighborsColors();
}

bool Board::verifyTileForCorner() {
    // Vérifier en fonction de sa position si les couleurs de ses angles sont bonnes
    if (this->currentRow_ == 0 && this->currentColumn_ == 0) {
        // Angle haut gauche
//        cout << "Angle Haut gauche" << endl;
        // Cet angle est seulement bon si la couleur du haut est la même que la couleur de gauche
        return this->currentTile_.getLeftColor() == this->currentTile_.getTopColor();
    } else if (this->currentRow_ == 0 && this->currentColumn_ == this->totalColumns_ - 1) {
        // Angle haut droit
//        cout << "Angle haut droit" << endl;
        return (this->currentTile_.getTopColor() == this->currentTile_.getRightColor());
    } else if (this->currentRow_ == (this->totalRows_ - 1) && this->currentColumn_ == 0) {
        // Angle bas gauche
//        cout << "Angle bas gauche" << endl;
        return (this->currentTile_.getLeftColor() == this->currentTile_.getBottomColor());
    } else if (this->currentRow_ == (this->totalRows_ - 1) && this->currentColumn_ == (this->totalColumns_ - 1)) {
        // Angle bas droit
//        cout << "Angle bas droit" << endl;
        return (this->currentTile_.getBottomColor() == this->currentTile_.getRightColor());
    }
    cout << "Erreur dans la fonction verifyTileForCorner()" << endl;
    return true;
}

bool Board::verifyBordersColors() {
    int r = this->currentRow_;
    int c = this->currentColumn_;

//    cout << "r :" << r << endl;
//    cout << "c :" << c << endl;

    if (r == 0) {
        // Si c'est une tile sur la bordure du haut
//        cout << borderColor << endl;
        return (this->currentTile_.getTopColor() == this->borderColor);
    } else if (c == 0) {
        // Si c'est une tile sur la bordure de gauche
//        cout << this->currentTile_.getLeftColor() << endl;
//        cout << this->borderColor << endl;
        return (this->currentTile_.getLeftColor() == this->borderColor);
    } else if (r == this->totalRows_ - 1) {
        // Si c'est une tile sur la bordure du bas
        return (this->currentTile_.getBottomColor() == this->borderColor);
    } else if (c == this->totalColumns_ - 1) {
        // Si c'est une tile sur la bordure de droite
        return (this->currentTile_.getRightColor() == this->borderColor);
    }
    return true;
}

bool Board::verifyNeighborsColors() {
//    cout << "verifyNeighborsColors()" << endl;
    bool isGood = true;

    int r = currentRow_;
    int c = currentColumn_;

    // Vérification des couleurs si c'est un angle
    if ((r == 0 || r == totalRows_ - 1) && (c == 0 || c == totalColumns_ - 1)) {
//        cout << "Angle de la mort qui tue" << endl;
        return verifyCornersColors();
    }

    // Assignation des tiles voisines en fonction de la position de la tile actuelle
    Tile leftTile;
    Tile topTile;
    Tile rightTile;
    Tile bottomTile;

    if (r == 0) {
//        cout << "Tile du haut" << endl;
        leftTile = board_[r][c - 1];
        topTile = defaultTile_;
        rightTile = defaultTile_;
        bottomTile = defaultTile_;
    } else if (r == totalRows_ - 1) {
//        cout << "Tile du bas" << endl;
        leftTile = board_[r][c - 1];
        topTile = board_[r - 1][c];
        rightTile = defaultTile_;
        bottomTile = defaultTile_;
    } else if (((r > 0) && (r < (totalRows_ - 1))) && ((c > 0) && (c < (totalColumns_ - 1)))) {
//        cout << "Tile du milieu" << endl;
        leftTile = board_[r][c - 1];
        topTile = board_[r - 1][c];
        rightTile = this->defaultTile_;
        bottomTile = this->defaultTile_;
    } else if (c == 0) {
//        cout << "Tile de gauche" << endl;
        leftTile = defaultTile_;
        topTile = board_[r - 1][c];
        rightTile = defaultTile_;
        bottomTile = defaultTile_;
    } else if (c == totalColumns_ - 1) {
//        cout << "Tile de droite" << endl;
        leftTile = board_[r][c - 1];
        topTile = board_[r - 1][c];
        rightTile = defaultTile_;
        bottomTile = defaultTile_;
    }

    // Vérifier les que les couleurs de la tile actuelle sont bonnes en fonction des couleurs de ses voisins
    isGood = ((leftTile.isEmpty()) || (leftTile.getRightColor() == currentTile_.getLeftColor())) &&
             ((topTile.isEmpty()) || (topTile.getBottomColor() == currentTile_.getTopColor())) &&
             ((rightTile.isEmpty()) || (rightTile.getLeftColor() == currentTile_.getRightColor())) &&
             ((bottomTile.isEmpty()) || (bottomTile.getTopColor() == currentTile_.getBottomColor()));
    return isGood;
}

bool Board::verifyCornersColors() {
    if (currentRow_ == 0 && currentColumn_ == 0) {
        // Angle haut gauche
        return currentTile_.getLeftColor() == currentTile_.getTopColor();
    } else if (currentRow_ == 0 && currentColumn_ == totalColumns_ - 1) {
        // Angle haut droit
        return currentTile_.getLeftColor() == board_[currentRow_][currentColumn_ - 1].getRightColor();
    } else if (currentRow_ == (totalRows_ - 1) && currentColumn_ == 0) {
        // Angle bas gauche
        return (currentTile_.getTopColor() == board_[currentRow_ - 1][currentColumn_].getBottomColor());
    } else if (currentRow_ == (totalRows_ - 1) && currentColumn_ == (totalColumns_ - 1)) {
        // Angle bas droit
        return (currentTile_.getLeftColor() == board_[currentRow_][currentColumn_ - 1].getRightColor()) &&
               (currentTile_.getTopColor() == board_[currentRow_ - 1][currentColumn_].getBottomColor());
    }
    cout << "Erreur dans la fonction verifyCornersColors()" << endl;
    return false;
}

vector<vector<Tile>> Board::getBoard() {
    return this->board_;
}