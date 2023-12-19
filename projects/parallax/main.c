#include <genesis.h>
#include <resources.h>
#include "inc/background.h"
#include "inc/parallax.h"

// Parallax relative speed.
#define LAYER_A_SPEED -2
#define LAYER_B_SPEED -1

int main() {
    u16 tile_index = TILE_USER_INDEX;
    u16 bg_a_offset = 0, bg_b_offset = 0;

    // Inserting background on screen.
    PRINT_BG(BG_B, PAL0, bg1, tile_index);

    // Inserting foreground on screen.
    PRINT_BG(BG_A, PAL1, fg1, tile_index);

    // Setting up scrooling configuratiion.
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    // Main Loop.
    while(1) {
        // Paralax effect.
        PARALAX_HORIZONTAL_PLANE_SPEED(BG_B, bg_b_offset, LAYER_B_SPEED);
        PARALAX_HORIZONTAL_PLANE_SPEED(BG_A, bg_a_offset, LAYER_A_SPEED);

        // End of the frame.
        SYS_doVBlankProcess();
    }
    return 0;
}