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

bool threadsManager(Board& finalBoard, Board board, int tileIndex, vector<bool> tilesUsed);
void threadLauncher(Board& finalBoard, Board board, int tileIndex, vector<bool> tilesUsed, bool& resolved);
bool threadsRecursiveResolver(Board& finalBoard, Board board, int tileIndex, vector<bool> tilesUsed, bool &resolved);

bool threadsPoolManager(Board& finalBoard, Board board, int tileIndex, vector<bool> tilesUsed);
void threadPoolLauncher(Board& finalBoard, Board board, int tileIndex, vector<bool> tilesUsed, bool& resolved);

int cpt = 0;
const int MAX_THREADS = 10;

// g++ main.cpp board/board.cpp board/tile/tile.cpp file/file.cpp -o main -l pthread

int main() {
    File fichier("5_5.txt");
    vector<string> file = fichier.readFile();

    Board board(file);
    Board finalBoard(file);

    vector<Tile> tilesList = board.getListTiles();

    auto start = std::chrono::high_resolution_clock::now();

    bool resolved = false;
//    sequentialRecursiveResolver(finalBoard, 0, vector<bool>(tilesList.size()));
    threadsManager(finalBoard, board, 0, vector<bool>(tilesList.size(), resolved));
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

bool threadsManager(Board& finalBoard, Board board, int tileIndex, vector<bool> tilesUsed) {
    bool resolved = false;
    // J'ai x tiles, elle sera lancé x fois dans x threads
    // Chaque thread aura une tile différente
    int nbTiles = board.getListTiles().size();
    vector<thread> threads(nbTiles);

    for (int i = 0; i < nbTiles; i++) {
        board.pushTile(i);
//        if (board.verifyTile()) {
            tilesUsed[i] = true;
            cout << "Tile i : " << i << " est utilisée" << endl;
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
    return false;
}

void threadLauncher(Board& finalBoard, Board board, int tileIndex, vector<bool> tilesUsed, bool& resolved) {
    if(resolved) {
        return;
    } else {
        Board boardX = board;
        if(threadsRecursiveResolver(finalBoard, board, tileIndex + 1, std::move(tilesUsed), resolved)) {
            return;
        }
    }
}

bool threadsPoolManager(Board& finalBoard, Board board, int tileIndex, vector<bool> tilesUsed) {
    cpt = 0;
    bool resolved = false;
    // J'ai x tiles, elle sera lancé x fois dans x threads
    // Chaque thread aura une tile différente
    int nbTiles = board.getListTiles().size();
    vector<thread> threads(nbTiles);

    int index = 0;
    while (index < nbTiles && !resolved) {
        if(cpt < MAX_THREADS) {
            board.pushTile(index);
//            if (board.verifyTile()) {
                tilesUsed[index] = true;
                cout << "Tile index : " << index << " est utilisée" << endl;
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
    return false;
}

void threadPoolLauncher(Board& finalBoard, Board board, int tileIndex, vector<bool> tilesUsed, bool& resolved) {
    cpt++;
    if(resolved) {
        cpt--;
        return;
    } else {
        Board boardX = board;
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