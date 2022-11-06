#ifndef __CITIES_H__
#define __CITIES_H__

#include <glib.h>

typedef GHashTable *Cities;
typedef struct ride *Ride;
typedef GPtrArray *Rides;

/**
 * @brief
 *
 * @return Cities
 */
Cities new_cities(void);

/**
 * @brief
 *
 * @param cities
 */
void free_cities(Cities cities);

/**
 * @brief
 *
 * @param cities
 * @param city
 * @param cost
 */
void add_cities_ride(Cities cities, Ride r);

/**
 * @brief Get the cities city avg cost object
 *
 * @param cities
 * @param city
 * @return double
 */
double get_cities_city_avg_cost(Cities cities, char *city);

/**
 * @brief
 *
 * @param cities
 * @param city
 * @param dateA
 * @param dateB
 * @return double
 */
double get_cities_city_avg_dist_in_range(Cities cities, char *city, char *dateA,
                                         char *dateB);

#endif
