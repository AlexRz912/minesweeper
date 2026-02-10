#pragma once
#include "../data/structs.h"

int getRow(int neighborIndex);
int getCol(int neighborIndex);
int mineIsBomb(struct MineSweeper * mineGrid, int row, int col);