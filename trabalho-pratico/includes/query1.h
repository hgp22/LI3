#ifndef __QUERY1_H__
#define __QUERY1_H__

#include "driver.h"
#include "user.h"
#include <stdint.h>

/**
 * @brief
 *
 * @param u
 * @return char*
 */
char *user_to_q1_string(User u);

/**
 * @brief
 *
 * @param d
 * @return char*
 */
char *driver_to_q1_string(Driver d);

#endif
