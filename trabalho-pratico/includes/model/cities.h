#ifndef __CITIES_H__
#define __CITIES_H__

#include <glib.h>

typedef GHashTable *Cities;
typedef struct ride *Ride;
typedef GArray *Rides;

/**
 * @brief Creat a new Cities
 *
 * @return Cities created
 */
Cities cities_new(void);

/**
 * @brief Frees Cities
 *
 * @param cities Cities to be freed
 */
void cities_free(Cities cities);

/**
 * @brief Adds ride to cities
 *
 * @param cities
 * @param r
 */
void cities_add_ride(Cities cities, Ride r);

/**
 * @brief Get the cities city avg cost object
 *
 * @param cities
 * @param city
 */
double cities_get_city_avg_cost(Cities cities, char *city);

/**
 * @brief
 *
 * @param cities
 * @param city
 * @param dateA
 * @param dateB
 * @return double
 */
double cities_get_city_avg_dist_in_range(Cities cities, char *city, char *dateA, char *dateB);

#endif
