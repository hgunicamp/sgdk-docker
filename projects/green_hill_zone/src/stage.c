#include "../inc/stage.h"

#define INIT_STAGE_MAP(ptr_stage, ptr_tiles, ptr_map, layer, tile_attributes, init_x, init_y) do { \
    VDP_loadTileSet(ptr_tiles, TILE_USER_INDEX, DMA); \
    ptr_stage->map = MAP_create(ptr_map, layer, tile_attributes); \
    ptr_stage->x_pos = init_x; \
    ptr_stage->y_pos = init_y; \
    MAP_scrollTo(ptr_stage->map, init_x, init_y); \
} while(0)

void stage_init(
    stage_struct *stage, const TileSet *tiles, const MapDefinition *map, VDPPlane layer, u16 tile_attributes, u16 x_pos,  u16 y_pos
) {
    INIT_STAGE_MAP(stage, tiles, map, layer, tile_attributes, x_pos, y_pos);
}

void stage_scroll(stage_struct *stage, u16 x_speed,  u16 y_speed) {
    stage->x_pos += x_speed;
    stage->y_pos += y_speed;
    MAP_scrollTo(stage->map, stage->x_pos, stage->y_pos);
}
