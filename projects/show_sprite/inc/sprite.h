#ifndef _SPRITE_H_
#define _SPRITE_H_

typedef struct {
    Sprite *sprite;
    s16 x_pos;
    s16 y_pos;
    u16 sprite_attributes;
} sprite_struct;

#define INIT_SPRITE(palette_index, resource) do { \
    SPR_init(); \
    PAL_setPalette(palette_index, resource.palette->data, DMA); \
} while(0)

#define ADD_SPRITE(resource, sprite_index) do { \
    sprite_index.sprite = SPR_addSprite( \
        &resource, sprite_index.x_pos, sprite_index.y_pos, sprite_index.sprite_attributes \
    ); \
} while(0)

#endif
