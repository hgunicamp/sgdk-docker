#ifndef _AXEL_ACTIONS_H_
#define _AXEL_ACTIONS_H_

#define AXEL_IDLE_ANIMATION 1
#define AXEL_WALKING_ANIMATION 2
#define AXEL_INIT_X_POS 25
#define AXEL_INIT_Y_POS 50

#include <sprite_eng.h>
#include "sprite.h"
#include "joystick_mediator.h"

extern joystick_mediator_struct axel_joy_mediator;

void install_axel_sprite(sprite_struct *axel, const SpriteDefinition *axel_sprite);

#endif
