#ifndef __DRIVERS_H__
#define __DRIVERS_H__

#include "driver.h"
#include <glib.h>

typedef GHashTable *Drivers;

/**
 * @brief
 *
 * @return Drivers
 */
Drivers new_drivers(void);

/**
 * @brief
 *
 * @param drivers
 * @param driver
 * @return gboolean
 */
gboolean insert_driver(Drivers drivers, long id, Driver driver);

/**
 * @brief
 *
 * @param data
 */
static void _key_destroyed(gpointer data);

/**
 * @brief
 *
 * @param data
 */
static void _value_destroyed(gpointer data);

#endif
