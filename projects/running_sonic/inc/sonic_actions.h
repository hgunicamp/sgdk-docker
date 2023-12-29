#ifndef _SONIC_ACTIONS_H_
#define _SONIC_ACTIONS_H_

#include <sprite_eng.h>
#include "sprite.h"
#include "states.h"

/**
 * \brief
 *     Sonic sprite initialization.
 * \param sonic
 *    Sprite struct reference.
 * \param sonic_sprite,
 *    Reference to sonic resource.
 * \param world_state
 *    Reference to the state of the world.
 */
void install_sonic_sprite(
    sprite_struct *sonic,
    const SpriteDefinition *sonic_sprite,
    state_struct *world_state
);

/**
 * \brief
 *    Update the sonic's sptrite after the end of the frame.
 * \param sonic
 *    Sprite struct reference.
 */
void update_sonic_sprite_after_frame(sprite_struct *sonic);

#endif
