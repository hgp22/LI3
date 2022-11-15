#ifndef __CITIES_H__
#define __CITIES_H__

#include <glib.h>

typedef GHashTable *Cities;
typedef struct ride *Ride;
typedef GPtrArray *Rides;
typedef GPtrArray *Query2;

/**
 * @brief Creates a new Cities
 *
 * @param rides Rides to add to city
 * @param drivers Drivers to add to city
 * @return Cities created
 */
Cities cities_new(Rides rides, Query2 drivers);

/**
 * @brief Frees Cities
 *
 * @param cities Cities to be freed
 */
void cities_free(Cities cities);

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
double cities_get_city_avg_dist_in_range(Cities cities, char *city, char *dateA,
                                         char *dateB);

/**
 * @brief Gets top N driver in a city
 *
 * @param cities Cities collection
 * @param city City name
 * @param N Number of drivers to get
 * @return List of top N drivers
 */
Query2 cities_get_city_top_N_drivers(Cities cities, char *city, int N);

#endif
