#include <genesis.h>
#include <resources.h>
#include "inc/background.h"
#include "inc/sprite.h"

int main() {
    u16 tile_index = TILE_USER_INDEX;
    background_struct background, foreground;
    sprite_struct sonic;

    // Init the backgrounds layers.
    background_init(&background, BG_B, PAL0, &bg1);
    background_init(&foreground,  BG_A, PAL1, &fg1);

    // Initialising the sprite struct.
    sonic.x_pos = 50;
    sonic.y_pos = 150;
    sonic.sprite_attributes = TILE_ATTR(PAL2, FALSE, FALSE, FALSE);

    // Inserting background on screen.
    PRINT_BG(background, tile_index);
    PRINT_BG(foreground, tile_index);

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
