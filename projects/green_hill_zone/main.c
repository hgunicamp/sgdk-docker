#include <genesis.h>
#include "res/resources.h"
#include "inc/stage.h"

int main() {

stage_struct green_hill_zone;

PAL_setPalette(PAL0, green_hill_palette.data, DMA);
u16 green_hill_tiles_attr = TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USER_INDEX);
stage_init(&green_hill_zone, &green_hill_tileset, &green_hill_map, BG_B, green_hill_tiles_attr, 0, 768);

    // Main Loop.
    while(1) {
        stage_scroll(&green_hill_zone, 1, 0);
        // End of the frame.
        SYS_doVBlankProcess();
    }
    return 0;
}
