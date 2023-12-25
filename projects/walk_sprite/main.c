#include <genesis.h>
#include "res/resources.h"
#include "inc/background.h"
#include "inc/sprite.h"

int main() {
    u16 tile_index = TILE_USER_INDEX;
    background_struct background, foreground;
    sprite_struct axel;

    // Init the backgrounds layers.
    background_init(&background, BG_B, PAL0, &bg1);
    background_init(&foreground,  BG_A, PAL1, &fg1);

    // Initialising the sprite struct.
    axel.x_pos = 25;
    axel.y_pos = 50;
    axel.sprite_attributes = TILE_ATTR(PAL2, FALSE, FALSE, TRUE);

    // Inserting background on screen.
    PRINT_BG(background, tile_index);
    PRINT_BG(foreground, tile_index);

    // Sprite set up.
    SPR_init();
    INIT_SPRITE_PALETTE(PAL2, axel_sprite);
    INSTALL_SPRITE(axel_sprite, axel, 1);

    // Main Loop.
    while(1) {
        SPR_update();
        // End of the frame.
        SYS_doVBlankProcess();
    }
    return 0;
}
