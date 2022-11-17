#ifndef __CATALOG_H__
#define __CATALOG_H__

#include <glib.h>

typedef struct inputs *Inputs;
typedef struct user *User;
typedef struct driver *Driver;
typedef GHashTable *Users;
typedef GHashTable *Drivers;
typedef GPtrArray *Rides;
typedef GPtrArray *Query2;
typedef GPtrArray *Query3;
typedef struct catalog *Catalog;

/**
 * @brief Creates a new catalog
 *
 * @return Catalog created
 */
Catalog catalog_new();

/**
 * @brief Frees a catalog
 *
 * @param catalog Catalog to be freed
 */
void catalog_free(Catalog c);

/**
 * @brief Processes a basic catalog into a complete catalog capable of answering
 * any query
 *
 * @param c Catalog to be processed
 * @return Control integer
 */
int catalog_process(Catalog c);

/**
 * @brief Load users into catalog
 *
 * @param c Catalog where to load users
 * @param users Users to load into catalog
 */
void catalog_set_users(Catalog c, Users users);

/**
 * @brief Load drivers into catalog
 *
 * @param c Catalog where to load drivers
 * @param drivers Drivers to load into catalog
 */
void catalog_set_drivers(Catalog c, Drivers drivers);

/**
 * @brief Load rides into catalog
 *
 * @param c Catalog where to load rides
 * @param rides Rides to load into catalog
 */
void catalog_set_rides(Catalog c, Rides rides);

/**
 * @brief Get a user in catalog by username
 *
 * @param c Catalog to get user
 * @param username Username of user to be returned
 * @return User searched
 */
User catalog_get_user(Catalog c, char *username);

/**
 * @brief Get a driver in catalog by driver id
 *
 * @param c Catalog to get driver
 * @param id Id of driver to be returned
 * @return Driver searched
 */
Driver catalog_get_driver(Catalog c, long id);

/**
 * @brief Get the top N drivers by score
 *
 * @param c Catalog to be searched
 * @param N Number of drivers to be returned
 * @return List of top N drivers by score
 */
Query2 catalog_get_top_n_drivers_by_score(Catalog c, int N);

/**
 * @brief Get the top N users by distanced travelled
 *
 * @param c Catalog to be searched
 * @param N Number of users to be returned
 * @return List of top N users by distance travelled
 */
Query3 catalog_get_top_n_users_by_distance(Catalog c, int N);

/**
 * @brief Get rides average cost in a city
 *
 * @param c Catalog
 * @param city City
 * @return Rides average cost in a city
 */
double catalog_get_city_avg_cost(Catalog c, char *city);

/**
 * @brief Get rides average cost between two dates inclusive
 *
 * @param c Catalog
 * @param dateA First date
 * @param dateB Second date
 * @return Average ride cost between two dates inclusive
 */
double catalog_get_avg_cost_in_range(Catalog c, char *dateA, char *dateB);

/**
 * @brief Get average distance travelled in a city between two dates inclusive
 *
 * @param c Catalog
 * @param city Cidade
 * @param dateA First date
 * @param dateB Second date
 * @return Average distance travelled in a city between two dates inclusive
 */
double catalog_get_city_avg_dist_in_range(Catalog c, char *city, char *dateA,
                                          char *dateB);

/**
 * @brief
 *
 * @param c
 * @param city
 * @param N
 * @return Query2
 */
Query2 catalog_get_top_n_drivers_in_city(Catalog c, char *city, int N);

/**
 * @brief
 *
 * @param c
 * @param dateA
 * @param dateB
 * @return Query9
 */
Query9 catalog_get_rides_with_tip_in_range(Catalog c, char *dateA, char *dateB);

#endif
