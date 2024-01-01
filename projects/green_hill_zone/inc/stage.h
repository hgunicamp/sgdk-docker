#ifndef _STAGE_H_
#define _STAGE_H_

#include <types.h>
#include <vdp.h>
#include <vdp_tile.h>
#include <map.h>

/**  
 * \brief
 *     Stage structure.
 */
typedef struct {
    Map *map;
    u16 x_pos;
    u16 y_pos;
} stage_struct;

/** 
 * \brief
 *     Initializating a stage struct.
 * \param stage
 *     Reference to stage struct to be initializated.
 * \param tiles
 *     Reference to stage tiles.
 * \param map
 *     Reference to stage map.
 * \param layer
 *     Target layer.
 * \param tile_attributes
 *     Tiles attributes to be used.
 * \param x_pos
 *     Initial stage X position.
 * \param y_pos
 *     Initial stage Y position.
 */
void stage_init(
    stage_struct *stage, const TileSet *tiles, const MapDefinition *map, VDPPlane layer, u16 tile_attributes, u16 x_pos,  u16 y_pos
);

/** 
 * \brief
 *     Initializating a stage struct.
 * \param x_speed
 *     Axis X scrolling speed.
 * \param y_speed
 *     Axis Y scrolling speed.
 */
void stage_scroll(stage_struct *stage, u16 x_speed,  u16 y_speed);

#endif
