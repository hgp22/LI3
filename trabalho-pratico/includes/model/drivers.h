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
Drivers drivers_new(void);

/**
 * @brief
 *
 * @param drivers
 */
void drivers_free(Drivers drivers);

/**
 * @brief
 *
 * @param drivers
 * @param d
 * @return gboolean
 */
gboolean drivers_add_driver(Drivers drivers, Driver d);

/**
 * @brief Get the driver object
 *
 * @param drivers
 * @param id
 * @return Driver
 */
Driver drivers_get_driver(Drivers drivers, long id);

/**
 * @brief
 *
 * @param drivers
 * @return guint
 */
guint drivers_remove_inactive_accounts(Drivers drivers);

#endif
