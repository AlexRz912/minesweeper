#include "utils.h"

int getRow(int neighborIndex) {
    return neighborIndex / COLS;
}

int getCol(int neighborIndex) {
    return neighborIndex % COLS;
}

int mineIsBomb(struct MineSweeper * mineGrid, int row, int col) {
    return (mineGrid->mine[row][col] == 18);
}