#include "drivers.h"
#include "driver.h"

Drivers insert_driver(Drivers drivers, Driver driver)
{
    return g_slist_prepend(drivers, driver);
}
