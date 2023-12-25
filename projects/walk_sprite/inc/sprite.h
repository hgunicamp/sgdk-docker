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

#define INIT_SPRITE_PALETTE(palette_index, ptr_resource) do { \
    PAL_setPalette(palette_index, ptr_resource->palette->data, DMA); \
} while(0)

#define INSTALL_SPRITE(ptr_resource, ptr_sprite_index, idle_animation) do { \
    ptr_sprite_index->sprite = SPR_addSprite( \
        ptr_resource, ptr_sprite_index->x_pos, ptr_sprite_index->y_pos, ptr_sprite_index->sprite_attributes \
    ); \
    ptr_sprite_index->idle_animation_index = ptr_sprite_index->current_animation_index = idle_animation; \
    SPR_setAnim(ptr_sprite_index->sprite, idle_animation); \
} while(0)

#endif
