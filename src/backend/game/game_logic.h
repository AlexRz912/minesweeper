#pragma once

#include "../data/structs.h"

void addBombsToGrid(struct MineSweeper * mineGrid);
void addCluesToGrid(struct MineSweeper * mineGrid, const enum SurroundingClues dirs[]);
void hideGrid(struct MineSweeper * mineGrid);