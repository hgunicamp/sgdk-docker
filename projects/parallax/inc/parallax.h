#ifndef _PARALLAX_H_
#define _PARALLAX_H_

#define PARALAX_HORIZONTAL_PLANE_SPEED(layer_index, layer_offset, layer_speed) do { \
    VDP_setHorizontalScroll(layer_index, layer_offset); \
    layer_offset += layer_speed; \
} while(0)

#endif