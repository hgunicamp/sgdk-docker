#ifndef _SPRITE_H_
#define _SPRITE_H_

#define  SPRITE_NO_ANIMATE -1

#include <dma.h>
#include <sprite_eng.h>

typedef struct {
    Sprite *sprite;
    s16 x_pos;
    s16 y_pos;
    s16 idle_animation_index;
    s16 current_animation_index;
    u16 sprite_attributes;
} sprite_struct;

#define INIT_SPRITE_PALETTE(palette_index, resource) do { \
    PAL_setPalette(palette_index, resource.palette->data, DMA); \
} while(0)

#define INSTALL_SPRITE(resource, sprite_index, idle_animation) do { \
    sprite_index.sprite = SPR_addSprite( \
        &resource, sprite_index.x_pos, sprite_index.y_pos, sprite_index.sprite_attributes \
    ); \
    sprite_index.idle_animation_index = sprite_index.current_animation_index = idle_animation; \
    SPR_setAnim(sprite_index.sprite, idle_animation); \
} while(0)

#endif
