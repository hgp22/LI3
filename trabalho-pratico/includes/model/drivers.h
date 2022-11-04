#ifndef __DRIVERS_H__
#define __DRIVERS_H__

#include <glib.h>

typedef struct driver *Driver;
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
 */
void free_drivers(Drivers drivers);

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

#endif
