#include <genesis.h>
#include <resources.h>
#include "inc/background.h"
#include "inc/sprite.h"

// Parallax relative speed.
#define LAYER_A_SPEED -2
#define LAYER_B_SPEED -1

int main() {
    u16 tile_index = TILE_USER_INDEX;
    Sprite *sonic;

    // Inserting background on screen.
    PRINT_BG(BG_B, PAL0, bg1, tile_index);
    // Inserting foreground on screen.
    PRINT_BG(BG_A, PAL1, fg1, tile_index);

    // Sprit set up.
    INIT_SPRITE(PAL2, sonic_sprite);
    ADD_SPRITE_ON(PAL2, sonic, sonic_sprite, 50, 150);

    // Main Loop.
    while(1) {
        SPR_update();
        // End of the frame.
        SYS_doVBlankProcess();
    }
    return 0;
}