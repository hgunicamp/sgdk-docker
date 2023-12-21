#ifndef _PARALLAX_H_
#define _PARALLAX_H_

#define PARALAX_HORIZONTAL_PLANE_SPEED(background, layer_speed) do { \
    VDP_setHorizontalScroll(background.layer_index, background.bg_offset); \
    background.bg_offset += layer_speed; \
} while(0)

#endif
