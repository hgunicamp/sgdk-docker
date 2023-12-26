#ifndef _JOYSTICK_MEDIATOR_H_
#define _JOYSTICK_MEDIATOR_H_

#include "sprite.h"
#include <sprite_eng.h>
#include <joy.h>

typedef struct {
    sprite_struct *sprite_index;
    u16 (*up_action)(sprite_struct *sprite);
    u16 (*down_action)(sprite_struct *sprite);
    u16 (*rigth_action)(sprite_struct *sprite);
    u16 (*left_action)(sprite_struct *sprite);
} joystick_mediator_struct;

#define JOY_TRIGGER_IDLE_ACTION(mediator, action_alread_taken) do { \
    if (action_alread_taken || \
        mediator.sprite_index->current_animation_index == mediator.sprite_index->idle_animation_index \
    ) { \
       break; \
    } \
    mediator.sprite_index->current_animation_index = mediator.sprite_index->idle_animation_index; \
    SPR_setAnim(mediator.sprite_index->sprite, mediator.sprite_index->idle_animation_index); \
} while(0)

#define JOY_TRIGGER_X_AXIS_ACTION(mediator, joy_value, action_alread_taken) do { \
    if (!(joy_value & (BUTTON_RIGHT | BUTTON_LEFT))) break; \
    action_alread_taken |= (joy_value & BUTTON_RIGHT) ? \
        mediator.rigth_action(mediator.sprite_index)  :  \
        mediator.left_action(mediator.sprite_index); \
} while(0)

#define JOY_TRIGGER_Y_AXIS_ACTION(mediator, joy_value, action_alread_taken) do { \
    if (!(joy_value & (BUTTON_DOWN | BUTTON_UP))) break; \
    action_alread_taken |= (joy_value & BUTTON_DOWN) ? \
        mediator.down_action(mediator.sprite_index)  :  \
        mediator.up_action(mediator.sprite_index); \
} while(0)

#endif
