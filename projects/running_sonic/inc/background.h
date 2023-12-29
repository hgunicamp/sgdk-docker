#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include <dma.h>
#include <vdp.h>
#include <vdp_bg.h>
#include "states.h"

/**
 * \brief
 *     Defining background struct.
 */
typedef struct {
    VDPPlane layer_index;
    u16 palette_index;
    Image *resource;
    u16 x_pos;
    u16 y_pos;
    u16 bg_offset;
    const u16 *bg_speed;
} background_struct;

// Parallax speed.
const u16 BACKGROUND_PARALLAX_SPEED = { 0, 0, 0, 1, 0};
const u16 FOREGROUND_PARALLAX_SPEED = { 0, 0, 1, 2, 1};

/**
 * \brief
 *     Initializating the background layer.
 * \param background
 *     Background reference.
 * \param layer
 *     Background layer.
 * \param palette_index
 *     Used palette.
 * \param resource
 *     Reference to the used resource.
 * \param bg_speed
 *     Parallax speed reference
 */
void background_init(
    background_struct *background,
    VDPPlane layer,
    u16 palette_index,
    const Image *resource,
    const u16 *bg_speed
);

// Printing a background layer.
#define BACKGROUND_PRINT(background, tile_index, priority) do { \
    PAL_setPalette(\
        background.palette_index, \
        background.resource->palette->data, \
        DMA \
    ); \
    VDP_drawImageEx( \
        background.layer_index, \
        background.resource, \
        TILE_ATTR_FULL(background.palette_index, priority, FALSE, FALSE, tile_index), \
        background.x_pos, \
        background.y_pos, \
        FALSE, \
        DMA \
    ); \
    tile_index += background.resource->tileset->numTile; \
} while(0)

/**
 * \brief
 *     Update the background state based on the state of the world.
 * \param background
 *     Background reference.
 * \param world_state
 *     World state reference.
 */
void background_update_frame(background_struct *background, state_struct *world_state);

#endif
