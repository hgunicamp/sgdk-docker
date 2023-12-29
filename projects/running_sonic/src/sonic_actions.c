#include <types.h>
#include <vdp.h>
#include <vdp_tile.h>
#include "../inc/sprite.h"
#include "../inc/states.h"
#include "../inc/sonic_actions.h"
#include "../inc/joystick_mediator.h"

joystick_mediator_struct sonic_joy_mediator;

const u16 SONIC_ANIMATION[] = { 1, 0, 2, 3, 4, 5, 6 };

void set_sonic_animation(joystick_mediator_struct *mediator, enum states state) {
    sprite_struct *sonic = (sprite_struct *) mediator->resource_index;
    mediator->world_state->state = state;
    sonic->current_animation_index = SONIC_ANIMATION[state];
    SPR_setAnim(sonic->sprite, SONIC_ANIMATION[state]);
    SPR_setHFlip(sonic->sprite, !i(mediator->world_state->facing_right));
}

void sonic_set_idle_state(joystick_mediator_struct *mediator) {
    set_sonic_animation(mediator, IDLE);
}

void sonic_set_flip_state(joystick_mediator_struct *mediator) {
    mediator->world_state->facing_right = !(mediator->world_state->facing_right);
    mediator->dpad_lock_frames = 30;
    set_sonic_animation(mediator, FLIP);
}

void sonic_set_speedind_up_state(joystick_mediator_struct *mediator) {
    mediator->dpad_lock_frames = 50;
    set_sonic_animation(mediator, SPEED_UP);
}

void sonic_set_running_state(joystick_mediator_struct *mediator) {
    set_sonic_animation(mediator, RUNNING);
}

void sonic_set_slow_dow_state(joystick_mediator_struct *mediator) {
    mediator->dpad_lock_frames = 20;
    set_sonic_animation(mediator, SLOW_DOWN);
}

void sonic_set_face_up_state(joystick_mediator_struct *mediator) {
    mediator->dpad_lock_frames = 30;
    set_sonic_animation(mediator, FACING_UP);
}

void sonic_set_face_dow_state(joystick_mediator_struct *mediator) {
    mediator->dpad_lock_frames = 30;
    set_sonic_animation(mediator, FACING_DOWN);
}

#define SONIC_CONNECT_STRUCTURES(mediator, ptr_sprite, ptr_world_state) do { \
    ptr_world_state->state = IDLE; \
    ptr_world_state->facing_right = TRUE; \
    mediator.world_state = ptr_world_state; \
    mediator.resource_index = (void *) ptr_sprite; \
    mediator.dpad_lock_frames = 0; \
    mediator.button_lock_frames = 0; \
    mediator.joy = JOY_1; \
} while(0)

void install_sonic_sprite(
    sprite_struct *sonic,
    const SpriteDefinition *sonic_sprite,
    state_struct *world_state
) {
    SONIC_CONNECT_STRUCTURES(sonic_joy_mediator, sonic, world_state);
}
