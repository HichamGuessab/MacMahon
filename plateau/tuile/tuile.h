#ifndef MACMAHON_TUILE_H
#define MACMAHON_TUILE_H

#include "string"
#include <map>
#include <vector>

using namespace std;

class Tuile {
public:
    Tuile();
    Tuile(char left, char top, char right, char bottom);
    Tuile(char leftColor, char topColor, char rightColor, char bottomColor, int row, int column);

    char getLeftColor();
    char getTopColor();
    char getRightColor();
    char getBottomColor();

    void displayTopLine();
    void displayMiddleLine();
    void displayBottomLine();
    void display();

    bool isEmpty();

private:
    char leftColor;
    char topColor;
    char rightColor;
    char bottomColor;

    string leftANSIColor;
    string topANSIColor;
    string rightANSIColor;
    string bottomANSIColor;
    map<char, string> ANSIColors = {
            {'N', "\x1B[0m"},
            {'R', "\x1B[31m"},
            {'G', "\x1B[32m"},
            {'B', "\x1B[34m"}
    };
};

#endif // MACMAHON_TUILE_H
