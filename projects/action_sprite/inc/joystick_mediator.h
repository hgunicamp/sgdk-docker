#ifndef _JOYSTICK_MEDIATOR_H_
#define _JOYSTICK_MEDIATOR_H_

#include "sprite.h"
#include <sprite_eng.h>
#include <joy.h>

#define JOY_NO_ACTION_TAKEN 0
#define JOY_ACTION_TAKEN 1

static u16 joy_last_event[JOY_NUM] = { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };

typedef struct joy_mediator {
    sprite_struct *sprite_index;
    s16 lock_frames;
    u16 (*up_action)(struct joy_mediator *mediator);
    u16 (*down_action)(struct joy_mediator *mediator);
    u16 (*rigth_action)(struct joy_mediator *mediator);
    u16 (*left_action)(struct joy_mediator *mediator);
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
        mediator.rigth_action(&mediator)  :  \
        mediator.left_action(&mediator); \
} while(0)

#define JOY_TRIGGER_Y_AXIS_ACTION(mediator, joy_value, action_alread_taken) do { \
    if (!(joy_value & (BUTTON_DOWN | BUTTON_UP))) break; \
    action_alread_taken |= (joy_value & BUTTON_DOWN) ? \
        mediator.down_action(&mediator)  :  \
        mediator.up_action(&mediator); \
} while(0)

#define JOY_UNLOCK_MEDIATOR(ptr_mediator)  ptr_mediator->lock_frames = 0
#define JOY_MEDIATOR_IS_LOCKED(ptr_mediator) ptr_mediator->lock_frames > 0
#define JOY_GET_CURRENT_STATE(joy) joy_last_event[joy]

u16 joystick_mediator_no_button_action(joystick_mediator_struct *mediator);

u16 joystick_mediator_get_last_joy_event(u16 joy);

void joystick_mediator_reduce_locking_time(joystick_mediator_struct *mediator);

void joystck_event_listener(u16 joy, u16 changed, u16 state);

#endif
