#ifndef _JOYSTICK_MEDIATOR_H_
#define _JOYSTICK_MEDIATOR_H_

#include <joy.h>
#include <types.h>

// Defines the maximun number of observed joysticks.
#define JOY_MAX_NUMBER (JOY_1 + 1)

/**
 *  Values to inform that a previous action has alread been taken.
 */
#define JOY_NO_ACTION_TAKEN 0x0000
#define JOY_ACTION_TAKEN 0x0001

// Obsevable joystick's events.
// DPAD Events.
#define JOY_DPAD_IDLE 0x000
#define JOY_DPAD_PRESSED_RIGHT 0x001
#define JOY_DPAD_HOLDING_RIGHT 0x002
#define JOY_DPAD_RELEASED_RIGHT 0x004
#define JOY_DPAD_PRESSED_LEFT 0x008
#define JOY_DPAD_HOLDING_LEFT 0x010
#define JOY_DPAD_RELEASED_LEFT 0x020
#define JOY_DPAD_PRESSED_UP 0x040
#define JOY_DPAD_HOLDING_UP 0x080
#define JOY_DPAD_RELEASED_UP 0x100
#define JOY_DPAD_PRESSED_DOWN 0x200
#define JOY_DPAD_HOLDING_DOWN 0x400
#define JOY_DPAD_RELEASED_DOWN 0x800
// Action button events.
#define JOY_BUTTON_IDLE 0x000000
#define JOY_BUTTON_PRESSED_A 0x000001
#define JOY_BUTTON_HOLDING_A 0x000002
#define JOY_BUTTON_RELEASED_A 0x000004
#define JOY_BUTTON_PRESSED_B 0x000008
#define JOY_BUTTON_HOLDING_B 0x000010
#define JOY_BUTTON_RELEASED_B 0x000020
#define JOY_BUTTON_PRESSED_C 0x000040
#define JOY_BUTTON_HOLDING_C 0x000080
#define JOY_BUTTON_RELEASED_C 0x000100
#define JOY_BUTTON_PRESSED_X 0x000200
#define JOY_BUTTON_HOLDING_X 0x000400
#define JOY_BUTTON_RELEASED_X 0x000800
#define JOY_BUTTON_PRESSED_Y 0x001000
#define JOY_BUTTON_HOLDING_Y 0x002000
#define JOY_BUTTON_RELEASED_Y 0x004000
#define JOY_BUTTON_PRESSED_Z 0x008000
#define JOY_BUTTON_HOLDING_Z 0x010000
#define JOY_BUTTON_RELEASED_Z 0x020000
#define JOY_BUTTON_PRESSED_START 0x040000
#define JOY_BUTTON_HOLDING_START 0x080000
#define JOY_BUTTON_RELEASED_START 0x100000

/**
 * \brief
 *     Joystick event structure.
 */
typedef struct {
    bool dpad_chaged;
    bool action_changed;
    u16 dpad_event;
    u32 button_event;
} joystick_event_struct;

/**
 * Joystick's event buffer.
 */
extern joystick_event_struct joy_last_event[];

/**
 * \brief
 *     Mediotor to link a resource to a joystick event.
 */
typedef struct joy_mediator {
    void *resource_index;
    s16 dpad_lock_frames;
    s16 button_lock_frames;
    u16 joy;
    u16 (*idle_action)(struct joy_mediator *mediator);
    u16 (*released_up_action)(struct joy_mediator *mediator);
    u16 (*released_down_action)(struct joy_mediator *mediator);
    u16 (*released_rigth_action)(struct joy_mediator *mediator);
    u16 (*released_left_action)(struct joy_mediator *mediator);
    u16 (*pressed_up_action)(struct joy_mediator *mediator);
    u16 (*pressed_down_action)(struct joy_mediator *mediator);
    u16 (*pressed_rigth_action)(struct joy_mediator *mediator);
    u16 (*pressed_left_action)(struct joy_mediator *mediator);
    u16 (*holding_up_action)(struct joy_mediator *mediator);
    u16 (*holding_down_action)(struct joy_mediator *mediator);
    u16 (*holding_rigth_action)(struct joy_mediator *mediator);
    u16 (*holding_left_action)(struct joy_mediator *mediator);
    u16 (*released_button_a_action)(struct joy_mediator *mediator);
    u16 (*released_button_b_action)(struct joy_mediator *mediator);
    u16 (*released_button_c_action)(struct joy_mediator *mediator);
    u16 (*released_button_x_action)(struct joy_mediator *mediator);
    u16 (*released_button_y_action)(struct joy_mediator *mediator);
    u16 (*released_button_z_action)(struct joy_mediator *mediator);
    u16 (*released_button_start_action)(struct joy_mediator *mediator);
    u16 (*pressed_button_a_action)(struct joy_mediator *mediator);
    u16 (*pressed_button_b_action)(struct joy_mediator *mediator);
    u16 (*pressed_button_c_action)(struct joy_mediator *mediator);
    u16 (*pressed_button_x_action)(struct joy_mediator *mediator);
    u16 (*pressed_button_y_action)(struct joy_mediator *mediator);
    u16 (*pressed_button_z_action)(struct joy_mediator *mediator);
    u16 (*pressed_button_start_action)(struct joy_mediator *mediator);
    u16 (*holding_button_a_action)(struct joy_mediator *mediator);
    u16 (*holding_button_b_action)(struct joy_mediator *mediator);
    u16 (*holding_button_c_action)(struct joy_mediator *mediator);
    u16 (*holding_button_x_action)(struct joy_mediator *mediator);
    u16 (*holding_button_y_action)(struct joy_mediator *mediator);
    u16 (*holding_button_z_action)(struct joy_mediator *mediator);
    u16 (*holding_button_start_action)(struct joy_mediator *mediator);
} joystick_mediator_struct;

/**
 * \brief
 *     Force the mediator to be unlocked.
 * \param ptr_mediator
 *     Mediator reference.
 */
#define JOY_UNLOCK_MEDIATOR(ptr_mediator)  do { \
    ptr_mediator->dpad_lock_frames = 0; \
    ptr_mediator->button_lock_frames = 0; \
} while(0)

/**
 * \brief
 *     Verifies if a specific mediator's key is locked.
 * \param ptr_mediator
 *     Mediator reference.
 * \param key
 *     Mediator lock key.
 */
#define JOY_MEDIATOR_IS_LOCKED(ptr_mediator, key) (ptr_mediator->key##_lock_frames > 0)

/**
 * \brief
 *     Gets the current joystick event.
 * \param joy
 *     Joystick's key.
 */
#define JOY_GET_CURRENT_EVENT(joy) joy_last_event[joy]

/**
 * \brief
 *     Handle event whe the joystick is complete idel.
 * \param ptr_mediator
 *     Mediator reference.
 */
#define JOY_HANDLE_IDLE_EVENT(ptr_mediator) do { \
    if (JOY_MEDIATOR_IS_LOCKED(ptr_mediatori, dpad) && JOY_MEDIATOR_IS_LOCKED(ptr_mediatori, button) break; \
    if ( \
        JOY_GET_CURRENT_EVENT(prt_mediator->joy)->dpad_event == JOY_DPAD_IDLE && \
        JOY_GET_CURRENT_EVENT(prt_mediator->joy)->button_event == JOY_BUTTON_IDLE \
        ) ptr_mediator->idle_action(ptr_mediator); \
} while(0)

/**
 * \brief
 *     Default function to be used as NOP when no action is installed.
 * \param ptr_mediator
 *     Mediator reference.
 */
u16 joystick_mediator_no_button_action(joystick_mediator_struct *mediator);

/**
 * \brief
 *     Reduces the locking time if necessary.
 * \param ptr_mediator
 *     Mediator reference.
 */
void joystick_mediator_reduce_locking_time(joystick_mediator_struct *mediator);

/**
 * \brief
 *     Joystick initialization function.
 */
void joystick_init();

/**
 * \brief
 *     Updating joystick event function.
 * \param joy
 *     Joystick's key.
 *     
 */
void joystick_update_last_event(u16 joy);

#endif
