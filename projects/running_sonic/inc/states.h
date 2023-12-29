#ifndef _STATES_H_
#define _STATES_H_

/**
 * \brief
 *    Possible states in the world.
 */
enum states {
    ST_IDLE, ST_FLIP, ST_SPEED_UP, ST_RUNNING, ST_SLOW_DOWN, ST_FACING_UP, ST_FACING_DOWN
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
