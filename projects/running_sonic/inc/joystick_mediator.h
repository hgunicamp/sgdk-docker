#ifndef _JOYSTICK_MEDIATOR_H_
#define _JOYSTICK_MEDIATOR_H_

#include <types.h>
#include <joy.h>
#include "states.h"

// Defines the maximun number of observed joysticks.
#define JOY_MAX_NUMBER (JOY_1 + 1)

// Obsevable joystick's events.
// DPAD Events.
#define JOY_DPAD_PRESSED_RIGHT 0x01
#define JOY_DPAD_RELEASED_RIGHT 0x02
#define JOY_DPAD_PRESSED_LEFT 0x04
#define JOY_DPAD_RELEASED_LEFT 0x08
#define JOY_DPAD_PRESSED_UP 0x10
#define JOY_DPAD_RELEASED_UP 0x20
#define JOY_DPAD_PRESSED_DOWN 0x40
#define JOY_DPAD_RELEASED_DOWN 0x80
#define JOY_DPAD_IDLE (JOY_DPAD_RELEASED_DOWN | JOY_DPAD_RELEASED_UP | JOY_DPAD_RELEASED_LEFT | JOY_DPAD_RELEASED_RIGHT )
#define JOY_DPAD_ONLY_RIGHT (JOY_DPAD_RELEASED_DOWN | JOY_DPAD_RELEASED_UP | JOY_DPAD_RELEASED_LEFT | JOY_DPAD_PRESSED_RIGHT )
#define JOY_DPAD_ONLY_LEFT (JOY_DPAD_RELEASED_DOWN | JOY_DPAD_RELEASED_UP | JOY_DPAD_PRESSED_LEFT | JOY_DPAD_RELEASED_RIGHT )
#define JOY_DPAD_ONLY_UP (JOY_DPAD_RELEASED_DOWN | JOY_DPAD_PRESSED_UP | JOY_DPAD_RELEASED_LEFT | JOY_DPAD_RELEASED_RIGHT )
#define JOY_DPAD_ONLY_DOWN (JOY_DPAD_PRESSED_DOWN | JOY_DPAD_RELEASED_UP | JOY_DPAD_RELEASED_LEFT | JOY_DPAD_RELEASED_RIGHT )
// Action button events.
#define JOY_BUTTON_PRESSED_A 0x0001
#define JOY_BUTTON_RELEASED_A 0x0002
#define JOY_BUTTON_PRESSED_B 0x0004
#define JOY_BUTTON_RELEASED_B 0x0008
#define JOY_BUTTON_PRESSED_C 0x0010
#define JOY_BUTTON_RELEASED_C 0x0020
#define JOY_BUTTON_PRESSED_X 0x0040
#define JOY_BUTTON_RELEASED_X 0x0080
#define JOY_BUTTON_PRESSED_Y 0x0100
#define JOY_BUTTON_RELEASED_Y 0x0200
#define JOY_BUTTON_PRESSED_Z 0x0400
#define JOY_BUTTON_RELEASED_Z 0x0800
#define JOY_BUTTON_PRESSED_START 0x1000
#define JOY_BUTTON_RELEASED_START 0x2000
#define JOY_BUTTON_PRESSED_MODE 0x4000
#define JOY_BUTTON_RELEASED_MODE 0x8000
#define JOY_BUTTON_IDLE (JOY_BUTTON_RELEASED_MODE | JOY_BUTTON_RELEASED_START | JOY_BUTTON_RELEASED_Z | JOY_BUTTON_RELEASED_Y | JOY_BUTTON_RELEASED_X | JOY_BUTTON_RELEASED_C | JOY_BUTTON_RELEASED_B | JOY_BUTTON_RELEASED_A )

/**
 * \brief
 *     Joystick event structure.
 */
typedef struct {
    bool dpad_chaged;
    bool action_changed;
    u8 dpad_event;
    u16 button_event;
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
    state_struct *world_state;
    void *resource_index;
    s16 dpad_lock_frames;
    s16 button_lock_frames;
    u16 joy;
    void (**actions)(struct joy_mediator *mediator);
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
#define JOY_HANDLE_IDLE_EVENT(ptr_mediator, idle_func_index) do { \
    if (JOY_MEDIATOR_IS_LOCKED(ptr_mediator, dpad) && JOY_MEDIATOR_IS_LOCKED(ptr_mediator, button) break; \
    if ( \
        JOY_GET_CURRENT_EVENT(prt_mediator->joy)->dpad_event == JOY_DPAD_IDLE && \
        JOY_GET_CURRENT_EVENT(prt_mediator->joy)->button_event == JOY_BUTTON_IDLE \
        ) ptr_mediator->actions[idle_func_index](ptr_mediator); \
} while(0)

/**
 * \brief
 *     General template for mediator glue logic.
 * \param expression
 *     Logic expression which triggers an action.
 * \param func
 *     Mediator fucntion to be executed.
 * \param lock_key
 *     Locking key to be evaluated befeore excute the function.
 * \param ptr_mediator
 *     Mediator reference.
 */
#define JOY_HANDLE_EVENT_TEMPLATE(expression, func_index, lock_key, ptr_mediator) do { \
    if (JOY_MEDIATOR_IS_LOCKED(ptr_mediator, lock_key) || !(expression)) break; \
    ptr_mediator->actions[func_index](ptr_mediator); \
} while(0)

/**
 * \brief
 *     Filter a event accaording to rules.
 * \param filter_rules
 *     Bitwise AND filter.
 * \param event_value
 *     Original value.
 */
#define JOY_HANDLE_FILTER_JOYSTICK_EVENT(filter_rules, event_value) ((filter_rules) & event_value)

/**
 * \brief
 *     Filter a event accaording to rules.
 * \param filter_rules
 *     Bitwise EXCLUSIVE filter.
 * \param event_value
 *     Original value.
 */
#define JOY_HANDLE_FILTER_JOYSTICK_EXCLUSIVE_EVENT(filter_rules, event_value) (!((filter_rules) ^ event_value))

/**
 * \brief
 *     Joystick initialization function.
 * \param joy
 *     Joystick's key.
 */
void joystick_init(u16 joy);

/**
 * \brief
 *     Updating joystick state at the end of a frame.
 * \param mediator
 *     Mediator reference.
 */
void joystick_update_state_after_frame(joystick_mediator_struct *mediator);

#endif
