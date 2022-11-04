#ifndef __CATALOG_H__
#define __CATALOG_H__

#include <glib.h>

typedef struct inputs *Inputs;
typedef struct user *User;
typedef struct driver *Driver;
typedef GHashTable *Users;
typedef GHashTable *Drivers;
typedef GPtrArray *Rides;
typedef GSList *Query2;
typedef GSList *Query3;
typedef struct catalog *Catalog;

/**
 * @brief
 *
 * @return Catalog
 */
Catalog new_catalog();

/**
 * @brief
 *
 * @param catalog
 */
void free_catalog(Catalog c);

/**
 * @brief
 *
 * @param q3
 */
void free_query3(Query3 q3);

/**
 * @brief Set the catalog users object
 *
 * @param c
 * @param users
 */
void set_catalog_users(Catalog c, Users users);

/**
 * @brief Set the catalog drivers object
 *
 * @param c
 * @param drivers
 */
void set_catalog_drivers(Catalog c, Drivers drivers);

/**
 * @brief Set the catalog rides object
 *
 * @param c
 * @param rides
 */
void set_catalog_rides(Catalog c, Rides rides);

/**
 * @brief Get the catalog top n drivers by score object
 *
 * @param c
 * @param N
 * @return Query2
 */
Query2 get_catalog_top_n_drivers_by_score(Catalog c, int N);

/**
 * @brief Get the catalog top n drivers by score object
 *
 * @param c
 * @param N
 * @return Query3
 */
Query3 get_catalog_top_n_users_by_distance(Catalog c, int N);

/**
 * @brief Get the catalog city avg cost object
 *
 * @param c
 * @param city
 * @return double
 */
double get_catalog_city_avg_cost(Catalog c, char *city);

/**
 * @brief Get the catalog rides object
 *
 * @param c
 * @return Rides
 */
Rides get_catalog_rides(Catalog c);

/**
 * @brief Get the catalog user object
 *
 * @param c
 * @param username
 * @return User
 */
User get_catalog_user(Catalog c, char *username);

/**
 * @brief Get the catalog driver object
 *
 * @param c
 * @param id
 * @return Driver
 */
Driver get_catalog_driver(Catalog c, long id);

/**
 * @brief
 *
 * @param c
 * @return int
 */
int process_catalog(Catalog c);

#endif
