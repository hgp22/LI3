#include "users.h"
#include "user.h"
#include <glib.h>

static gboolean _clean(gpointer key, gpointer value, gpointer user_data);
static void _key_destroyed(gpointer data);
static void _value_destroyed(gpointer data);

Users users_new(void)
{
    return g_hash_table_new_full(g_str_hash, g_str_equal,
                                 (GDestroyNotify)_key_destroyed,
                                 (GDestroyNotify)_value_destroyed);
}

void users_free(Users users)
{
    g_hash_table_destroy(g_steal_pointer(&users));
}

gboolean users_add_user(Users users, User u)
{
    return g_hash_table_insert(users, user_get_username(u), u);
}

User users_get_user(Users users, char *username)
{
    return g_hash_table_lookup(users, username);
}

guint users_remove_inactive_accounts(Users users)
{
    return g_hash_table_foreach_remove(users, (GHRFunc)_clean, NULL);
}

static gboolean _clean(gpointer key, gpointer value, gpointer user_data)
{
    User u = (User)value;
    if (user_get_account_status(u) == U_Inactive) {
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
    user_free(data);
}
