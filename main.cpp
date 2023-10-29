#include <iostream>
#include <vector>
#include "fichier.h"
#include "tuile.h"

using namespace std;

string directory = "/Users/hicham/Library/Mobile Documents/com~apple~CloudDocs/Documents/University/M1_ILSEN/UE_Conception_Logicielle/Programmation_Parrallele/MacMahon/";

int main() {
    Fichier fichier(directory + "5_5.txt");
    vector<string> file = fichier.readFile();
    cout << file[0] << endl;

    Tuile maTuile('G', 'B', 'R', 'G');
    maTuile.afficher();
    return 0;
}