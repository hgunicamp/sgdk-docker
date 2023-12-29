#include <genesis.h>
#include "res/resources.h"
#include "inc/sprite.h"
#include "inc/background.h"
#include "inc/states.h"
#include "inc/sonic_actions.h"

int main() {
    u16 tile_index = TILE_USER_INDEX;
    background_struct background, foreground;
    sprite_struct sonic;
    state_struct world_state;

    // Init the backgrounds layers.
    background_init(&background, BG_B, PAL0, &bg1, BACKGROUND_PARALLAX_SPEED);
    background_init(&foreground,  BG_A, PAL1, &fg1, FOREGROUND_PARALLAX_SPEED);

    // Inserting background on screen.
    PRINT_BG(background, tile_index, FALSE);
    PRINT_BG(foreground, tile_index, FALSE);

    // Setting up scrooling configuration.
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    // Sprite set up.
    SPR_init();
    install_sonic_sprite(&sonic, &sonic_sprite, &world_state);

    // Main Loop.
    while(1) {
        // Updating the screen elements.
        update_sonic_sprite_after_frame();
        background_update_frame(&bg1, &world_state);
        background_update_frame(&fg1, &world_state);
        SPR_update();
        // End of the frame.
        SYS_doVBlankProcess();
    }
    return 0;
}
