#include <iostream>
#include <utility>
#include <vector>
#include <chrono>
#include <thread>

#include "file/file.h"
#include "board/tile/tile.h"
#include "board/board.h"

using namespace std;

bool sequentialRecursiveResolver(Board& board, int tileIndex, vector<bool> tilesUsed);

void threadsManager(Board& finalBoard, Board board, int tileIndex, vector<bool> tilesUsed);
void threadLauncher(Board& finalBoard, Board board, int tileIndex, vector<bool> tilesUsed, bool& resolved);
bool threadsRecursiveResolver(Board& finalBoard, Board board, int tileIndex, vector<bool> tilesUsed, bool &resolved);

void threadsPoolManager(Board& finalBoard, Board board, int tileIndex, vector<bool> tilesUsed);
void threadPoolLauncher(Board& finalBoard, Board board, int tileIndex, vector<bool> tilesUsed, bool& resolved);

atomic<int> cpt = 0;
const int MAX_THREADS = 5;

int main(int argc, char** argv) {
    File fichier("4_4.txt");
    vector<string> file = fichier.readFile();

    Board board(file);
    Board finalBoard(file);

    vector<Tile> tilesList = board.getListTiles();

    auto start = std::chrono::high_resolution_clock::now();

    bool resolved = false;
    sequentialRecursiveResolver(finalBoard, 0, vector<bool>(tilesList.size()));
//    threadsManager(finalBoard, board, 0, vector<bool>(tilesList.size(), resolved));
//    threadsPoolManager(finalBoard, board, 0, vector<bool>(tilesList.size(), resolved));

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    finalBoard.display();

    std::cout << "Temps d'éxecution: " << duration << " millisecondes" << std::endl;

    return 0;
}

bool sequentialRecursiveResolver(Board& board, int tileIndex, vector<bool> tilesUsed) {
    if (tileIndex == board.getTotalRows() * board.getTotalColumns()) {
        return true;
    }

    for (int i = 0; i < board.getListTiles().size(); i++) {
        if (!board.isTileUsed(tilesUsed, i)) {
            board.pushTile(i);

            if (board.verifyTile()) {
                tilesUsed[i] = true;
                if (sequentialRecursiveResolver(board, tileIndex + 1, tilesUsed)) {
                    return true;
                }
                tilesUsed[i] = false;
            }
            board.popTile();
        }
    }
    return false;
}

void threadsManager(Board& finalBoard, Board board, int tileIndex, vector<bool> tilesUsed) {
    bool resolved = false;
    // J'ai x tiles, elle sera lancé x fois dans x threads
    // Chaque thread aura une tile différente
    int nbTiles = board.getListTiles().size();
    vector<thread> threads(nbTiles);

    for (int i = 0; i < nbTiles; i++) {
        board.pushTile(i);
        // Je n'ai pas rajouté ce if pour avoir de meilleurs résultats (sinon il n'y a pas de lancement de threads pour les premières mauvaises tuiles)
//        if (board.verifyTile()) {
            tilesUsed[i] = true;
            cout << "Tile index : " << i << " est utilisée" << endl;
            threads[i] = thread(threadLauncher, ref(finalBoard), board, tileIndex, tilesUsed, ref(resolved));
        tilesUsed[i] = false;
//        }
        board.popTile();
    }
    for(int i = 0; i < nbTiles; i++) {
        if(threads[i].joinable()) {
            threads[i].join();
        }
    }
}

void threadLauncher(Board& finalBoard, Board board, int tileIndex, vector<bool> tilesUsed, bool& resolved) {
    if(resolved) {
        return;
    } else {
        if(threadsRecursiveResolver(finalBoard, board, tileIndex + 1, std::move(tilesUsed), resolved)) {
            return;
        }
    }
}

void threadsPoolManager(Board& finalBoard, Board board, int tileIndex, vector<bool> tilesUsed) {
    cpt = 0;
    bool resolved = false;
    int nbTiles = board.getListTiles().size();
    vector<thread> threads(nbTiles);

    // Correspond au nombre de tâches dans mon bassin
    int index = 0;
    while (index < nbTiles && !resolved) {
        if(cpt < MAX_THREADS) {
            board.pushTile(index);
            // Je n'ai pas rajouté ce if pour avoir de meilleurs résultats (sinon il n'y a pas de lancement de threads pour les premières mauvaises tuiles)
//            if (board.verifyTile()) {
                tilesUsed[index] = true;
                cout << "Tuile index : " << index << " est utilisée" << endl;
                cout << "Cpt : " << cpt << endl;
                threads[index] = thread(threadPoolLauncher, ref(finalBoard), board, tileIndex, tilesUsed,
                                        ref(resolved));
            tilesUsed[index] = false;
//            }
            board.popTile();
            index++;
        }
    }
    for(int i = 0; i < nbTiles; i++) {
        if(threads[i].joinable()) {
            threads[i].join();
        }
    }
}

void threadPoolLauncher(Board& finalBoard, Board board, int tileIndex, vector<bool> tilesUsed, bool& resolved) {
    cpt++;
    if(resolved) {
        cpt--;
        return;
    } else {
        if(threadsRecursiveResolver(finalBoard, board, tileIndex + 1, std::move(tilesUsed), resolved)) {
            cpt--;
            return;
        }
    }
    cpt--;
}

bool threadsRecursiveResolver(Board& finalBoard, Board board, int tileIndex, vector<bool> tilesUsed, bool& resolved) {
    if(resolved) {
        return false;
    }
    if (tileIndex == board.getTotalRows() * board.getTotalColumns()) {
        finalBoard = board;
        resolved = true;
        return true;
    }

    for (int i = 0; i < board.getListTiles().size(); i++) {
        if(resolved) {
            return false;
        }
        if (!board.isTileUsed(tilesUsed, i)) {
            board.pushTile(i);

            if (board.verifyTile()) {
                tilesUsed[i] = true;
                if (threadsRecursiveResolver(finalBoard, board, tileIndex + 1, tilesUsed, resolved)) {
                    return true;
                }
                tilesUsed[i] = false;
            }
            board.popTile();
        }
    }
    return false;
}