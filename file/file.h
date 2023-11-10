#ifndef MACMAHON_FILE_H
#define MACMAHON_FILE_H

#include "fstream"
#include <vector>

using namespace std;

class File {
public:
    explicit File(string path);
    vector<string>readFile();
private:
    string path = "../boardsTxt/";
};

#endif // MACMAHON_FILE_H