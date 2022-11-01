#ifndef __CATALOG_H__
#define __CATALOG_H__

#include "drivers.h"
#include "inputs.h"
#include "query2.h"
#include "query3.h"
#include "rides.h"
#include "users.h"
#include <glib.h>

typedef struct catalog *Catalog;

/**
 * @brief
 *
 * @param i
 * @return Catalog
 */
Catalog init_catalog(Inputs i);

/**
 * @brief
 *
 * @param catalog
 */
void free_catalog(Catalog c);

/**
 * @brief Get the catalog users object
 *
 * @param c
 * @return Users
 */
Users get_catalog_users(Catalog c);

/**
 * @brief Get the catalog drivers object
 *
 * @param c
 * @return Drivers
 */
Drivers get_catalog_drivers(Catalog c);

/**
 * @brief Get the catalog query2 object
 *
 * @param c
 * @return Query2
 */
Query2 get_catalog_query2(Catalog c);

/**
 * @brief Get the catalog query3 object
 *
 * @param c
 * @return Query3
 */
Query3 get_catalog_query3(Catalog c);

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
 * @param driver1
 * @param driver2
 * @return gint
 */
static gint _driver_comparator(gconstpointer driver1, gconstpointer driver2);

/**
 * @brief
 *
 * @param user1
 * @param user2
 * @return gint
 */
static gint _user_comparator(gconstpointer user1, gconstpointer user2);

#endif
