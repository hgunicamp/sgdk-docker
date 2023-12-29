#ifndef _JOYSTICK_MEDIATOR_H_
#define _JOYSTICK_MEDIATOR_H_

#include <types.h>
#include <joy.h>
#include "states.h"

// Defines the maximun number of observed joysticks.
#define JOY_MAX_NUMBER (JOY_1 + 1)

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
