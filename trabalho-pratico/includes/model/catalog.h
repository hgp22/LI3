#ifndef __CATALOG_H__
#define __CATALOG_H__

#include <glib.h>

typedef struct inputs *Inputs;
typedef struct user *User;
typedef struct driver *Driver;
typedef GHashTable *Users;
typedef GHashTable *Drivers;
typedef GArray *Rides;
typedef GPtrArray *Query2;
typedef GPtrArray *Query3;
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
 * @param c
 * @return int
 */
int process_catalog(Catalog c);

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
 * @brief Get the catalog avg cost in range object
 *
 * @param c
 * @param dateA
 * @param dateB
 * @return double
 */
double get_catalog_avg_cost_in_range(Catalog c, char *dateA, char *dateB);

/**
 * @brief 
 * 
 * @param c 
 * @param city 
 * @param dateA 
 * @param dateB 
 * @return double 
 */
double avg_distance_in_city_in_date_range(Catalog c, char *city, char *dateA, char *dateB);

#endif
