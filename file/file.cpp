#include "iostream"
#include "file.h"

File::File(string path) {
    this->path = this->path + path;
}

vector<string> File::readFile() {
    cout << "Lecture du fichier : " << this->path << endl;
    vector<string> fileLines;
    ifstream file(this->path);
    if(file) {
        string line;
        while(getline(file, line)) {
            fileLines.push_back(line);
        }
        file.close();
    }
    else {
        cout << "ERROR: Impossible d'ouvrir le fichier en lecture." << endl;
    }
    return fileLines;
}

void File::setFileName(string fileName) {
    this->path = "../boardsTxt/" + fileName;
}