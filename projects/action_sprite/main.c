#include <genesis.h>
#include "res/resources.h"
#include "inc/background.h"
#include "inc/axel_actions.h"
#include "inc/joystick_mediator.h"

int main() {
    u16 tile_index = TILE_USER_INDEX;
    background_struct background, foreground;
    sprite_struct axel;

    // Installing Joystick listener.
    JOY_setEventHandler(joystick_event_listener);

    // Init the backgrounds layers.
    background_init(&background, BG_B, PAL0, &bg1);
    background_init(&foreground,  BG_A, PAL1, &fg1);

    // Inserting background on screen.
    PRINT_BG(background, tile_index, FALSE);
    PRINT_BG(foreground, tile_index, TRUE);

    // Sprite set up.
    SPR_init();
    install_axel_sprite(&axel, &axel_sprite);

    // Main Loop.
    while(1) {
        update_axel_sprite(&axel);
        SPR_update();
        // End of the frame.
        SYS_doVBlankProcess();
    }
    return 0;
}
