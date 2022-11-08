#ifndef __CITIES_H__
#define __CITIES_H__

#include <glib.h>

typedef GHashTable *Cities;
typedef struct ride *Ride;
typedef GArray *Rides;

/**
 * @brief Creates a new Cities
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
 * @param cities Cities to add ride to
 * @param r Ride to be added
 */
void cities_add_ride(Cities cities, Ride r);

/**
 * @brief Get the cities city avg cost object
 *
 * @param cities Cities to get average cost
 * @param city City name to fin in Cities
 */
double cities_get_city_avg_cost(Cities cities, char *city);

/**
 * @brief Gets the average distance travelled in a city between two dates
 *
 * @param cities Cities
 * @param city City
 * @param dateA First date
 * @param dateB Second date
 * @return Average distance
 */
double cities_get_city_avg_dist_in_range(Cities cities, char *city, char *dateA, char *dateB);

#endif
