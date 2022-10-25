#ifndef __CATALOG_H__
#define __CATALOG_H__

#include "drivers.h"
#include "rides.h"
#include "users.h"
#include <glib.h>

typedef struct catalog *Catalog;

/**
 * @brief
 *
 * @return Catalog
 */
Catalog init_catalog(void);

/**
 * @brief
 *
 * @param catalog
 */
void free_catalog(Catalog c);

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
 * @brief Get the catalog rides object
 *
 * @param c
 * @return Rides
 */
Rides get_catalog_rides(Catalog c);

#endif
