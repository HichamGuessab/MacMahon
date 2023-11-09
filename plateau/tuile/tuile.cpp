#include "tuile.h"
#include "iostream"

Tuile::Tuile() {
    this->leftColor = 'N';
    this->topColor = 'N';
    this->rightColor = 'N';
    this->bottomColor = 'N';

    this->leftANSIColor = ANSIColors['N'];
    this->topANSIColor = ANSIColors['N'];
    this->rightANSIColor = ANSIColors['N'];
    this->bottomANSIColor = ANSIColors['N'];
}

Tuile::Tuile(char left, char top, char right, char bottom) {
    this->leftColor = left;
    this->topColor = top;
    this->rightColor = right;
    this->bottomColor = bottom;

    this->leftANSIColor = ANSIColors[left];
    this->topANSIColor = ANSIColors[top];
    this->rightANSIColor = ANSIColors[right];
    this->bottomANSIColor = ANSIColors[bottom];
}

Tuile::Tuile(char leftColor, char topColor, char rightColor, char bottomColor, int row, int column) {
    this->leftColor = leftColor;
    this->topColor = topColor;
    this->rightColor = rightColor;
    this->bottomColor = bottomColor;

    this->leftANSIColor = ANSIColors[leftColor];
    this->topANSIColor = ANSIColors[topColor];
    this->rightANSIColor = ANSIColors[rightColor];
    this->bottomANSIColor = ANSIColors[bottomColor];
}

void Tuile::display() {
    displayTopLine();
    cout << endl;
    displayMiddleLine();
    cout << endl;
    displayBottomLine();
    cout << endl << endl;
}

void Tuile::displayTopLine() {
    cout << this-> ANSIColors['N'] << "   ";
    cout << this->topANSIColor << "███" << ANSIColors['N'];
    cout << this-> ANSIColors['N'] << "   ";
}

void Tuile::displayMiddleLine() {
    cout << this->leftANSIColor << "███" << ANSIColors['N'];
    cout << this-> ANSIColors['N'] << "   ";
    cout << this->rightANSIColor << "███" << ANSIColors['N'];
}

void Tuile::displayBottomLine() {
    cout << this-> ANSIColors['N'] << "   ";
    cout << this->bottomANSIColor << "███" << ANSIColors['N'];
    cout << this-> ANSIColors['N'] << "   ";
};

char Tuile::getLeftColor() {
    return this->leftColor;
}

char Tuile::getTopColor() {
    return this->topColor;
}

char Tuile::getRightColor() {
    return this->rightColor;
}

char Tuile::getBottomColor() {
    return this->bottomColor;
}

bool Tuile::isEmpty() {
    return this->leftColor == 'N' &&
           this->topColor == 'N' &&
           this->rightColor == 'N' &&
           this->bottomColor == 'N';
}