#include <types.h>
#include <vdp.h>
#include <vdp_tile.h>
#include "../inc/sprite.h"
#include "../inc/axel_actions.h"
#include "../inc/joystick_mediator.h"

#define AXEL_IDLE_ANIMATION 1
#define AXEL_WALKING_ANIMATION 2
#define AXEL_ATACK_ANIMATION 3
#define AXEL_ATACK_ANIMATION_FRAMES 60
#define AXEL_NONE_ACTION 0x0000
#define AXEL_WALK_ACTION 0x0001
#define AXEL_ATACK_ACTION 0x0002
#define AXEL_INIT_X_POS 25
#define AXEL_INIT_Y_POS 50
#define AXEL_UP_WALKING_LIMT 0
#define AXEL_DOWN_WALKING_LIMT 95
#define AXEL_LEFT_WALKING_LIMT -35
#define AXEL_RIGHT_WALKING_LIMT 235
#define AXEL_Y_SPEED 1
#define AXEL_X_SPEED 1

#define AXEL_ON_MAX_UP(y_pos) !(y_pos > AXEL_UP_WALKING_LIMT)
#define AXEL_ON_MAX_DOWN(y_pos) !(y_pos < AXEL_DOWN_WALKING_LIMT)
#define AXEL_ON_MAX_LEFT(x_pos) !(x_pos > AXEL_LEFT_WALKING_LIMT)
#define AXEL_ON_MAX_RIGHT(x_pos) !(x_pos < AXEL_RIGHT_WALKING_LIMT)

joystick_mediator_struct axel_joy_mediator;

u16 axel_up_action(joystick_mediator_struct *mediator) {
    sprite_struct *axel = mediator->sprite_index;
    if (JOY_MEDIATOR_IS_LOCKED(mediator) || AXEL_ON_MAX_UP(axel->y_pos)) return AXEL_NONE_ACTION;
    axel->y_pos -= AXEL_Y_SPEED;
    return AXEL_WALK_ACTION;
}

u16 axel_down_action(joystick_mediator_struct *mediator) {
    sprite_struct *axel = mediator->sprite_index;
    if (JOY_MEDIATOR_IS_LOCKED(mediator) || AXEL_ON_MAX_DOWN(axel->y_pos)) return AXEL_NONE_ACTION;
    axel->y_pos += AXEL_Y_SPEED;
    return AXEL_WALK_ACTION;
}

u16 axel_left_action(joystick_mediator_struct *mediator) {
    sprite_struct *axel = mediator->sprite_index;
    if (JOY_MEDIATOR_IS_LOCKED(mediator) || AXEL_ON_MAX_LEFT(axel->x_pos)) return AXEL_NONE_ACTION;
    axel->x_pos -= AXEL_X_SPEED;
    SPR_setHFlip(axel->sprite, FALSE);
    return AXEL_WALK_ACTION;
}

u16 axel_right_action(joystick_mediator_struct *mediator) {
    sprite_struct *axel = mediator->sprite_index;
    if (JOY_MEDIATOR_IS_LOCKED(mediator) || AXEL_ON_MAX_RIGHT(axel->x_pos)) return AXEL_NONE_ACTION;
    axel->x_pos += AXEL_X_SPEED;
    SPR_setHFlip(axel->sprite, TRUE);
    return AXEL_WALK_ACTION;
}

u16 axel_atack_action(joystick_mediator_struct *mediator) {
    if (JOY_MEDIATOR_IS_LOCKED(mediator)) return AXEL_NONE_ACTION;
    mediator->lock_frames = AXEL_ATACK_ANIMATION_FRAMES;
    return AXEL_ATACK_ACTION;
}

void install_axel_sprite(sprite_struct *axel, const SpriteDefinition *axel_sprite) {
    // Setting up the palette.
    INIT_SPRITE_PALETTE(PAL2, axel_sprite);

    // Setting up the mediator.
    axel_joy_mediator.sprite_index = axel;
    axel_joy_mediator.lock_frames = 0;
    axel_joy_mediator.joy = JOY_1;
    axel_joy_mediator.up_action = axel_up_action;
    axel_joy_mediator.down_action = axel_down_action;
    axel_joy_mediator.left_action = axel_left_action;
    axel_joy_mediator.rigth_action = axel_right_action;
    axel_joy_mediator.button_a_action = joystick_mediator_no_button_action;
    axel_joy_mediator.button_b_action = axel_atack_action;
    axel_joy_mediator.button_c_action = joystick_mediator_no_button_action;
    axel_joy_mediator.button_x_action = joystick_mediator_no_button_action;
    axel_joy_mediator.button_y_action = joystick_mediator_no_button_action;
    axel_joy_mediator.button_z_action = joystick_mediator_no_button_action;
    axel_joy_mediator.button_start_action = joystick_mediator_no_button_action;

    // Starting the sprite.
    axel->x_pos = AXEL_INIT_X_POS;
    axel->y_pos = AXEL_INIT_Y_POS;
    axel->sprite_attributes = TILE_ATTR(PAL2, FALSE, FALSE, TRUE);

    // Install axel's sprite.
    INSTALL_SPRITE(axel_sprite, axel, AXEL_IDLE_ANIMATION);
}

void update_axel_animation(sprite_struct * axel, u16 action_taken) {
    u16 next_animation;

    switch (action_taken) {
        case AXEL_ATACK_ACTION:
            axel->current_animation_index = AXEL_ATACK_ANIMATION;
            next_animation = AXEL_ATACK_ANIMATION;
            break;
        case AXEL_WALK_ACTION:
            next_animation = AXEL_WALKING_ANIMATION;
            break;
        default:
            next_animation = AXEL_IDLE_ANIMATION;
            break;
    }

    if (JOY_MEDIATOR_IS_LOCKED((&axel_joy_mediator))) {
        SPR_setAnim(axel->sprite, axel->current_animation_index);
        return;
    }
    axel->current_animation_index = next_animation;
    SPR_setAnim(axel->sprite, next_animation);
}

void update_axel_sprite(sprite_struct *axel) {
    u16 axel_action_taken = 0, joy_value = JOY_GET_CURRENT_STATE(axel_joy_mediator.joy);

    // Reducing the locking time if necessary.
    joystick_mediator_reduce_locking_time(&axel_joy_mediator);

    // Processing joystick state.
    JOY_TRIGGER_B_BUTTON_ACTION(axel_joy_mediator, joy_value, axel_action_taken);
    JOY_TRIGGER_Y_AXIS_ACTION(axel_joy_mediator, joy_value, axel_action_taken);
    JOY_TRIGGER_X_AXIS_ACTION(axel_joy_mediator, joy_value, axel_action_taken);
    
    // Udating sprite on the screen.
    update_axel_animation(axel, axel_action_taken);
    SPR_setPosition(axel->sprite, axel->x_pos, axel->y_pos);
}
