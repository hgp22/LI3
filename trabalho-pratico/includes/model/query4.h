#ifndef __QUERY4_H__
#define __QUERY4_H__

#include <glib.h>

typedef GHashTable *Query4;

/**
 * @brief
 *
 * @return Query4
 */
Query4 new_query4(void);

/**
 * @brief
 *
 * @param q4
 */
void free_query4(Query4 q4);

/**
 * @brief
 *
 * @param q4
 * @param city
 * @param cost
 */
void add_query4_ride_cost(Query4 q4, char *city, double cost);

/**
 * @brief Get the query4 city avg cost object
 *
 * @param q4
 * @param city
 * @return double
 */
double get_query4_city_avg_cost(Query4 q4, char *city);

#endif
