#include <genesis.h>
#include <resources.h>
#include "inc/background.h"

int main() {
    u16 tile_index = TILE_USER_INDEX;

    // Inserting background on screen.
    PRINT_BG(BG_B, PAL0, bg1, tile_index);

    // Inserting foreground on screen.
    tile_index += bg1.tileset->numTile;
    PRINT_BG(BG_A, PAL1, fg1, tile_index);

    // Main Loop.
    while(1) {
        SYS_doVBlankProcess();
    }
    return 0;
}