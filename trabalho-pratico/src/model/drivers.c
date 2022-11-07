#include "drivers.h"
#include "driver.h"
#include <glib.h>

static gboolean _clean(gpointer key, gpointer value, gpointer user_data);
static void _key_destroyed(gpointer data);
static void _value_destroyed(gpointer data);

Drivers drivers_new(void)
{
    return g_hash_table_new_full(g_int_hash, g_int_equal,
                                 (GDestroyNotify)_key_destroyed,
                                 (GDestroyNotify)_value_destroyed);
}

gboolean drivers_add_driver(Drivers drivers, Driver d)
{
    gint *k_id = g_new(gint, 1);
    *k_id = driver_get_id(d);
    return g_hash_table_insert(drivers, k_id, d);
}

void drivers_free(Drivers drivers)
{
    g_hash_table_destroy(g_steal_pointer(&drivers));
}

Driver drivers_get_driver(Drivers drivers, long id)
{
    return g_hash_table_lookup(drivers, &id);
}

guint drivers_remove_inactive_accounts(Drivers drivers)
{
    return g_hash_table_foreach_remove(drivers, (GHRFunc)_clean, NULL);
}

static gboolean _clean(gpointer key, gpointer value, gpointer user_data)
{
    Driver d = (Driver)value;
    if (driver_get_account_status(d) == D_Inactive) {
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
    driver_free(data);
}
