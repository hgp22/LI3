#ifndef __QUERY2_H__
#define __QUERY2_H__

#include "driver.h"
#include <glib.h>

typedef struct catalog *Catalog;

typedef GSList *Query2;

/**
 * @brief
 *
 * @param c
 * @param N
 */
void query2(Catalog c, int N);

/**
 * @brief
 *
 * @param d
 * @return char*
 */
static char *_driver_to_q2_string(Driver d);

#endif
