#ifndef MACMAHON_FILE_H
#define MACMAHON_FILE_H

#include "fstream"
#include <vector>

using namespace std;

class Fichier {
public:
    explicit Fichier(string path);
    vector<string>readFile();
private:
    string path;
};

#endif // MACMAHON_FILE_H