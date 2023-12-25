#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include <dma.h>
#include <vdp.h>
#include <vdp_bg.h>

// Defining background struct.
typedef struct {
    VDPPlane layer_index;
    u16 palette_index;
    Image *resource;
    u16 x_pos;
    u16 y_pos;
    u16 bg_offset;
} background_struct;

// Setting initial values to a background.
void background_init(background_struct *background, VDPPlane layer, u16 palette_index, const Image *resource);

// Printing a background layer.
#define PRINT_BG(background, tile_index) do { \
    PAL_setPalette(\
        background.palette_index, \
        background.resource->palette->data, \
        DMA \
    ); \
    VDP_drawImageEx( \
        background.layer_index, \
        background.resource, \
        TILE_ATTR_FULL(background.palette_index, FALSE, FALSE, FALSE, tile_index), \
        background.x_pos, \
        background.y_pos, \
        FALSE, \
        DMA \
    ); \
    tile_index += background.resource->tileset->numTile; \
} while(0)

#endif
