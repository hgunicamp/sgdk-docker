#ifndef _STATES_H_
#define _STATES_H_

/**
 * \brief
 *    Possible states in the world.
 */
enum states {
    IDLE, FLIP, SPEED_UP, RUNNING, SLOW_DOWN, FACING_UP, FACING_DOWN
};

/**
 * \brief
 *     World state information.
 */
typedef struct {
    bool facing_right;
    enum states state;
} state_struct;

#endif
