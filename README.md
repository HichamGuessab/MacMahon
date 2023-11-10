# MacMahon

## Build

```bash
g++ main.cpp board/board.cpp board/tile/tile.cpp file/file.cpp -o main -l pthread
./main X Y
```
**X :** Board to solve (`4`, `5` or `6`)  
**Y :** Algorithm used to solve the board (`S` (sequential), `T` (threaded) or `P` (thread pool))

## How it works

### Tile
A tile is a square which has `3` maximum colors (`red`, `green` and `blue`).  
A tile has `4` sides (`left`, `top`, `right`, `bottom`) and each side has a color.

### Board
The **board** is a square of size `n` where `n` is the number of tiles per side.  
A **board** has a list of tiles and by default, the board is empty.  
A tile can be added to the board if it is not already present.

### How to solve the board
- The borders must have the same color.
- Each side of a tile must have the same color as the side of the adjacent tile.

## Strategy used

```
The first tile is pushed in the top left corner
We verify if the tile is valid
    If the tile is valid :
        Push the next tile next to the previous tile
    If the tile is not valid : 
        The tile is popped and the next tile is placed next to the previous tile
```

The algorithm used is a **backtracking** algorithm, so it is recursive.  
The next tile is placed next to the previous tile, if the line is full, the next tile is placed on the next line.  
A variable is used to know if the tile is used or not.

### Sequential algorithm
The sequential algorithm is the simplest algorithm.  
The algorithm is executed in the main thread.

### Threaded algorithm
The threaded algorithm is the same as the sequential algorithm but each thread has its own board and start at a tile.  
For example, if we have a board of size `4`, we have `16` tiles, so we have `16` threads and each thread starts with a tile.

### Thread pool algorithm
The thread pool algorithm is the same as the threaded algorithm but there is a limit of threads launched at the same time.

Look at the code if you want more details...

## Resolution time 
| Algorithm\Board | Board 4x4 | Board 5x5 | Board 6x6 |
|:---------------:|:---------:|:---------:|:---------:|
|   Sequential    |   62 ms   | 40 689 ms | 1 376 ms  |
|    Threaded     |  191 ms   | 2 315 ms  | 5 432 ms  |
|   ThreadPool    |  157 ms   | 49 679 ms | 2 714 ms  |

Resolution time for each tray as a function of the algorithm

The time to solve the board is the time to find the first solution.  
The time is the average of 10 runs.