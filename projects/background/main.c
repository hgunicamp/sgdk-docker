#include <genesis.h>
#include <resources.h>

int main() {
    u16 tile_index = TILE_USER_INDEX;

    // Inserting background on screen.
    PAL_setPalette(PAL0, bg1.palette->data, DMA);
    VDP_drawImageEx(BG_B, &bg1, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, tile_index), 0, 0, FALSE, DMA);

    // Inserting foreground on screen.
    tile_index += bg1.tileset->numTile;
    PAL_setPalette(PAL1, fg1.palette->data, DMA);
    VDP_drawImageEx(BG_A, &fg1, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, tile_index), 0, 0, FALSE, DMA);

    // Main Loop.
    while(1) {
        SYS_doVBlankProcess();
    }
    return 0;
}