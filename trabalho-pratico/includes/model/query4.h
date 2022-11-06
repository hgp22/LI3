#ifndef __QUERY4_H__
#define __QUERY4_H__

#include <glib.h>

typedef GHashTable *Query4;
typedef struct city *City;
typedef struct ride *Ride;
typedef GArray *Rides;

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
void add_query4_ride(Query4 q4, Ride r);

/**
 * @brief Get the query4 city avg cost object
 *
 * @param q4
 * @param city
 * @return double
 */
double get_query4_city_avg_cost(Query4 q4, char *city);

/**
 * @brief 
 * 
 * @param q4 
 * @param city 
 * @param dateA 
 * @param dateB 
 * @return double 
 */
double avg_distance(Query4 q4, char *city, char *dateA, char *dateB);

#endif
