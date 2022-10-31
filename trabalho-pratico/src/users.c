#include "users.h"
#include "user.h"
#include <glib.h>

Users new_users(void)
{
    return g_hash_table_new_full(g_str_hash, g_str_equal,
                                 (GDestroyNotify)_key_destroyed,
                                 (GDestroyNotify)_value_destroyed);
}

gboolean insert_user(Users users, char *username, User user)
{
    return g_hash_table_insert(users, username, user);
}

User get_user(Users users, char *username)
{
    return g_hash_table_lookup(users, username);
}

static void _key_destroyed(gpointer data)
{
    g_free(data);
}

static void _value_destroyed(gpointer data)
{
    free_user(data);
}
