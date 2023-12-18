#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

// Printing a background layer.
#define PRINT_BG(layer_index, palette_index, resource, tile_index) do { \
    PAL_setPalette(palette_index, resource.palette->data, DMA); \
    VDP_drawImageEx(layer_index, &resource, TILE_ATTR_FULL(palette_index, FALSE, FALSE, FALSE, tile_index), 0, 0, FALSE, DMA); \
} while(0)

#endif
