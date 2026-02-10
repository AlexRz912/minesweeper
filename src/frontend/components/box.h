#pragma once

#include "../../backend/data/structs.h"

enum BoxPosition {
    LEFT_BOX = 0,
    MIDDLE_BOX = 1,
    RIGHT_BOX = 2,
    BOX_COUNT = 3
};

struct UIBoxDimensions {
    float positions[BOX_COUNT];
    float boxSize;
    float boxY;
};

extern struct UIBoxDimensions * boxDimensions;

void getBoxesDimensions(struct MineSweeper * grid);