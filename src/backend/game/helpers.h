#pragma once
#include "../data/structs.h"
#include "utils.h"

int* getAllowedDirections(int cellIndex, int* count);
void updateCluesAroundBomb(struct MineSweeper * mineGrid, int cellIndex, int * allowedDirs, int count);
void updateClue(struct MineSweeper * mineGrid, int neighborIndex);
void printGrid(struct MineSweeper * mineGrid);
int isIllegalDir(int cellIndex, int dir);
void addAllowedDirection(int isAllowed, int* allowed, int* count, int dir);
