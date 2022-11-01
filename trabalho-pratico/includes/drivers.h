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
 * @param drivers
 * @return guint
 */
guint remove_inactive_drivers(Drivers drivers);

/**
 * @brief
 *
 * @param key
 * @param value
 * @param user_data
 * @return gboolean
 */
static gboolean _clean(gpointer key, gpointer value, gpointer user_data);

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
