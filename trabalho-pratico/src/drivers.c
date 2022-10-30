#include "drivers.h"
#include "driver.h"
#include <glib.h>

Drivers new_drivers(void)
{
    return g_hash_table_new_full(g_int_hash, g_int_equal,
                                 (GDestroyNotify)_key_destroyed,
                                 (GDestroyNotify)_value_destroyed);
}

gboolean insert_driver(Drivers drivers, Driver driver)
{
    gint *k_id = g_new(gint, 1);
    *k_id = get_driver_id(driver);
    return g_hash_table_insert(drivers, k_id, driver);
}

static void _key_destroyed(gpointer data)
{
    g_free(data);
}

static void _value_destroyed(gpointer data)
{
    free_driver(data);
}
