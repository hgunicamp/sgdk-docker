#ifndef _SPRITE_H_
#define _SPRITE_H_

#define INIT_SPRITE(palette_index, resource) do { \
    SPR_init(); \
    PAL_setPalette(palette_index, resource.palette->data, DMA); \
} while(0)

#define ADD_SPRITE_ON(palette_index, sprite_index, resource, x_pos, y_pos) do { \
    sprite_index = SPR_addSprite(&resource, x_pos, y_pos, TILE_ATTR(palette_index, FALSE, FALSE, FALSE)); \
} while(0)

#endif
