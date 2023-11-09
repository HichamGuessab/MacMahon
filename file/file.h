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
    string path = "/Users/hicham/Library/Mobile Documents/com~apple~CloudDocs/Documents/University/M1_ILSEN/UE_Conception_Logicielle/Programmation_Parrallele/MacMahon/boardsTxt/";
};

#endif // MACMAHON_FILE_H