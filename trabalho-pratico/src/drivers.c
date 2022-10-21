#include "driver.h"
#include "drivers.h"

Drivers *insert_driver(Drivers *drivers, Driver *driver)
{
    return g_slist_prepend(drivers, driver);
}