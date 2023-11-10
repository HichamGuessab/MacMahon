#ifndef MACMAHON_FILE_H
#define MACMAHON_FILE_H

#include "fstream"
#include <vector>

using namespace std;

class File {
public:
    explicit File(string path);
    vector<string>readFile();
    void setFileName(string fileName);
private:
    string defaultPath = "/home/nas-wks01/users/uapv2102872/MacMahon/boardsTxt/";
    string relativePath = "../boardsTxt/";
    string path;
};

#endif // MACMAHON_FILE_H