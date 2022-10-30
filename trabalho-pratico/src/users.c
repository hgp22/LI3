#include "users.h"
#include "user.h"
#include <glib.h>

Users new_users(void)
{
    return g_hash_table_new_full(g_str_hash, g_str_equal,
                                 (GDestroyNotify)_key_destroyed,
                                 (GDestroyNotify)_value_destroyed);
}

gboolean insert_user(Users users, User user)
{
    return g_hash_table_insert(users, get_user_username(user), user);
}

static void _key_destroyed(gpointer data)
{
    g_free(data);
}

static void _value_destroyed(gpointer data)
{
    free_user(data);
}
