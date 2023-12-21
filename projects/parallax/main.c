#include <genesis.h>
#include <resources.h>
#include "inc/background.h"
#include "inc/parallax.h"

// Parallax relative speed.
#define LAYER_A_SPEED -2
#define LAYER_B_SPEED -1

int main() {
    u16 tile_index = TILE_USER_INDEX;
    background_struct background, foreground;

    // Init the backgrounds layers.
    background_init(&background, BG_B, PAL0, &bg1);
    background_init(&foreground,  BG_A, PAL1, &fg1);

    // Inserting background on screen.
    PRINT_BG(background, tile_index);
    PRINT_BG(foreground, tile_index);

    // Setting up scrooling configuration.
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    // Main Loop.
    while(1) {
        // Paralax effect.
        PARALAX_HORIZONTAL_PLANE_SPEED(background, LAYER_B_SPEED);
        PARALAX_HORIZONTAL_PLANE_SPEED(foreground, LAYER_A_SPEED);

        // End of the frame.
        SYS_doVBlankProcess();
    }
    return 0;
}