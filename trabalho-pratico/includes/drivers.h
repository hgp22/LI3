#ifndef __DRIVERS_H__
#define __DRIVERS_H__

#include "driver.h"
#include <glib.h>

typedef GSList Drivers;

/**
 * @brief 
 * 
 * @param drivers 
 * @param driver 
 * @return Drivers* 
 */
Drivers *insert_driver(Drivers *drivers, Driver *driver);

#endif
