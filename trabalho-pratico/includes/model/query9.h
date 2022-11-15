#ifndef __QUERY9_H__
#define __QUERY9_H__

#include <glib.h>

typedef GPtrArray *Query9;
typedef GPtrArray *Rides;

/**
 * @brief
 *
 * @param rides
 * @return Query9
 */
Query9 query9_new(Rides rides);

/**
 * @brief
 *
 * @param q9
 * @param dateA
 * @param dateB
 * @return Query9
 */
Query9 query9_rides_with_tips_in_range(Query9 q9, char *dateA, char *dateB);

#endif
