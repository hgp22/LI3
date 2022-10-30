#ifndef __QUERY1_H__
#define __QUERY1_H__

#include "driver.h"
#include "user.h"
#include <stdint.h>

/**
 * @brief 
 * 
 * @param c 
 * @param id 
 */
void query1(Catalog c, char *id);

/**
 * @brief
 *
 * @param u
 * @return char*
 */
static char *_user_to_q1_string(User u);

/**
 * @brief
 *
 * @param d
 * @return char*
 */
static char *_driver_to_q1_string(Driver d);

#endif
