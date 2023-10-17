#include "iostream"
#include "fichier.h"

Fichier::Fichier(string path) {
    this->path = path;
}

vector<string> Fichier::readFile() {
    cout << "Reading file: " << this->path << endl;
    vector<string> fichier;
    ifstream file(this->path);
    if(file) {
        string ligne;
        while(getline(file, ligne)) {
            fichier.push_back(ligne);
        }
    }
    else {
        cout << "ERROR: Impossible d'ouvrir le fichier en lecture." << endl;
    }
    return fichier;
}