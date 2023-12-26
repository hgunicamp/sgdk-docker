#include <genesis.h>
#include "../inc/background.h"

void background_init(
    background_struct *background, VDPPlane layer, u16 palette_index, const Image *resource
) {
    background->layer_index = layer;
    background->palette_index = palette_index;
    background->resource = (Image *) resource;
    background->x_pos = 0;
    background->y_pos = 0;
    background->bg_offset = 0;
}
