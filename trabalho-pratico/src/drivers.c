#include "drivers.h"
#include "driver.h"
#include <glib.h>

Drivers new_drivers(void)
{
    return g_hash_table_new_full(g_int_hash, g_int_equal,
                                 (GDestroyNotify)_key_destroyed,
                                 (GDestroyNotify)_value_destroyed);
}

gboolean insert_driver(Drivers drivers, long id, Driver driver)
{
    gint *k_id = g_new(gint, 1);
    *k_id = id;
    return g_hash_table_insert(drivers, k_id, driver);
}

Driver get_driver(Drivers drivers, long id)
{
    return g_hash_table_lookup(drivers, &id);
}

static void _key_destroyed(gpointer data)
{
    g_free(data);
}

static void _value_destroyed(gpointer data)
{
    free_driver(data);
}
