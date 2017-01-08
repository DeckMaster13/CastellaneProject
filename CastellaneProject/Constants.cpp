#include "Constants.h"

int TILE_SIZE = 16;
int CELLS_NUMBER_PER_LINE = 50;

void updateCellsNumberPerLine(int newValue)
{
   CELLS_NUMBER_PER_LINE = newValue;
}

void updateTileSize(int newValue)
{
   TILE_SIZE = newValue;
}
