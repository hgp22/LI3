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
 * @param d
 * @return gboolean
 */
gboolean insert_driver(Drivers drivers, Driver d);

/**
 * @brief Get the driver object
 * 
 * @param drivers 
 * @param id 
 * @return Driver 
 */
Driver get_driver(Drivers drivers, long id);

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
