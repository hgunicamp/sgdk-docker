#include <genesis.h>
#include "../inc/background.h"

void background_init(
    background_struct *background,
    VDPPlane layer,
    u16 palette_index,
    const Image *resource,
    const u16 *bg_speed
) {
    background->layer_index = layer;
    background->palette_index = palette_index;
    background->resource = (Image *) resource;
    background->x_pos = 0;
    background->y_pos = 0;
    background->bg_offset = 0;
    background->bg_speed = bg_speed;
}

void background_update_frame(background_struct *background, state_struct *world_state) {
    u16 speed = background->bg_speed[world_state->state];
    VDP_setHorizontalScroll(background->layer_index, background->bg_offset);
    background->bg_offset += (world_state->facing_right) ? -speed : speed;
}
