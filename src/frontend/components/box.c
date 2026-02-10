#include <stdlib.h>
#include "box.h"

struct UIBoxDimensions * boxDimensions = NULL;

void getBoxesDimensions(struct MineSweeper * grid) {
    boxDimensions = malloc(sizeof(struct UIBoxDimensions));
    if (!boxDimensions) return;
    
    boxDimensions->boxSize = 80.0f;
    boxDimensions->boxY = 20.0f;
    boxDimensions->positions[LEFT_BOX] = grid->grid_x;
    boxDimensions->positions[MIDDLE_BOX] = grid->grid_x + (grid->grid_width - boxDimensions->boxSize) / 2;
    boxDimensions->positions[RIGHT_BOX] = grid->grid_x + grid->grid_width - boxDimensions->boxSize;
}
