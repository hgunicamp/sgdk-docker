#include <types.h>
#include <vdp.h>
#include <vdp_tile.h>
#include "../inc/sprite.h"
#include "../inc/axel_actions.h"

joystick_mediator_struct axel_joy_mediator;

void install_axel_sprite(sprite_struct *axel, const SpriteDefinition *axel_sprite) {
    // Setting up the palette.
    INIT_SPRITE_PALETTE(PAL2, axel_sprite);

    // Starting the sprite.
    axel->x_pos = AXEL_INIT_X_POS;
    axel->y_pos = AXEL_INIT_Y_POS;
    axel->sprite_attributes = TILE_ATTR(PAL2, FALSE, FALSE, TRUE);

    // Install axel's sprite.
    INSTALL_SPRITE(axel_sprite, axel, AXEL_IDLE_ANIMATION);
}
