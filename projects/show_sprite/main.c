#include <genesis.h>
#include <resources.h>
#include "inc/background.h"
#include "inc/sprite.h"

int main() {
    u16 tile_index = TILE_USER_INDEX;
    sprite_struct sonic;

    // Initialising the sprite struct.
    sonic.x_pos = 50;
    sonic.y_pos = 150;
    sonic.sprite_attributes = TILE_ATTR(PAL2, FALSE, FALSE, FALSE);

    // Inserting background on screen.
    PRINT_BG(BG_B, PAL0, bg1, tile_index);
    // Inserting foreground on screen.
    PRINT_BG(BG_A, PAL1, fg1, tile_index);

    // Sprit set up.
    INIT_SPRITE(PAL2, sonic_sprite);
    ADD_SPRITE(sonic_sprite, sonic);

    // Main Loop.
    while(1) {
        SPR_update();
        // End of the frame.
        SYS_doVBlankProcess();
    }
    return 0;
}