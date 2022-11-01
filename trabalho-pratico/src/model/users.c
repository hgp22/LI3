#include "users.h"
#include "user.h"
#include <glib.h>

Users new_users(void)
{
    return g_hash_table_new_full(g_str_hash, g_str_equal,
                                 (GDestroyNotify)_key_destroyed,
                                 (GDestroyNotify)_value_destroyed);
}

gboolean insert_user(Users users, User u)
{
    return g_hash_table_insert(users, get_user_username(u), u);
}

User get_user(Users users, char *username)
{
    return g_hash_table_lookup(users, username);
}

guint remove_inactive_users(Users users)
{
    return g_hash_table_foreach_remove(users, (GHRFunc)_clean, NULL);
}

static gboolean _clean(gpointer key, gpointer value, gpointer user_data)
{
    User u = (User)value;
    if (get_user_account_status(u) == U_Inactive) {
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
    free_user(data);
}
