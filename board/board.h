#ifndef MACMAHON_BOARD_H
#define MACMAHON_BOARD_H

#include "../file/file.h"
#include "tile/tile.h"
#include <vector>

using namespace std;

class Board {
public:
    Board(vector<string> file);
    void fillListTiles(vector<string> file);
    void pushTile(int index);
    void popTile();

    int getTotalRows();
    int getTotalColumns();

    Tile getCurrentTile();
    vector<Tile> getListTiles();
    bool isTileUsed(vector<bool> tilesUsed, int index);

    bool verifyTile();
    bool verifyTileForCorner();
    bool verifyBordersColors();
    bool verifyCornersColors();
    bool verifyNeighborsColors();

    vector<vector<Tile>> getBoard();

    void display();
    void displayListTiles();

private:
    int totalRows_;
    int totalColumns_;

    vector<Tile> listTiles_;
    vector<vector<Tile>> board_;

    // Tile actuelle dans le board (que je m'apprête à actualiser)
    Tile currentTile_;
    int currentRow_;
    int currentColumn_;

    int nextRow_;
    int nextColumn_;

    Tile defaultTile_ = Tile();

    char borderColor;
};

#endif // MACMAHON_BOARD_H
