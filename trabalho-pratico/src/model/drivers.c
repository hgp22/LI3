#include "drivers.h"
#include "driver.h"
#include <glib.h>

static gboolean _clean(gpointer key, gpointer value, gpointer user_data);
static void _key_destroyed(gpointer data);
static void _value_destroyed(gpointer data);

Drivers new_drivers(void)
{
    return g_hash_table_new_full(g_int_hash, g_int_equal,
                                 (GDestroyNotify)_key_destroyed,
                                 (GDestroyNotify)_value_destroyed);
}

gboolean insert_driver(Drivers drivers, Driver d)
{
    gint *k_id = g_new(gint, 1);
    *k_id = get_driver_id(d);
    return g_hash_table_insert(drivers, k_id, d);
}

Driver get_driver(Drivers drivers, long id)
{
    return g_hash_table_lookup(drivers, &id);
}

guint remove_inactive_drivers(Drivers drivers)
{
    return g_hash_table_foreach_remove(drivers, (GHRFunc)_clean, NULL);
}

static gboolean _clean(gpointer key, gpointer value, gpointer user_data)
{
    Driver d = (Driver)value;
    if (get_driver_account_status(d) == D_Inactive) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

static void _key_destroyed(gpointer data)
{
    g_free(data);
}

static void _value_destroyed(gpointer data)
{
    free_driver(data);
}
