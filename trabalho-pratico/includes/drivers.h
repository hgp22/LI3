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
gboolean insert_driver(Drivers drivers, Driver driver);

#endif
