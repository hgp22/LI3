#ifndef __DRIVERS_H__
#define __DRIVERS_H__

#include <glib.h>

typedef struct driver *Driver;
typedef GHashTable *Drivers;

/**
 * @brief Creates a new Driver
 *
 * @return Drivers created
 */
Drivers drivers_new(void);

/**
 * @brief Frees Drivers
 *
 * @param drivers Drivers to be freed
 */
void drivers_free(Drivers drivers);

/**
 * @brief Adds a Driver to Drivers
 *
 * @param drivers Drivers to add Driver
 * @param d Driver to add to Drivers
 * @return Control boolean
 */
gboolean drivers_add_driver(Drivers drivers, Driver d);

/**
 * @brief Get Driver from Drivers
 *
 * @param drivers Drivers to get Driver from
 * @param id Id to find Driver
 * @return Driver found
 */
Driver drivers_get_driver(Drivers drivers, long id);

/**
 * @brief Remove inactive driver accounts fromo Drivers
 *
 * @param drivers Drivers to remove innactive accounts
 * @return Control integer
 */
guint drivers_remove_inactive_accounts(Drivers drivers);

#endif
