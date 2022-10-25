#ifndef __CATALOG_H__
#define __CATALOG_H__

#include "drivers.h"
#include "inputs.h"
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
 * @brief Get the catalog rides object
 *
 * @param c
 * @return Rides
 */
Rides get_catalog_rides(Catalog c);

#endif
