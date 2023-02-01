#include "users.h"
#include "loader.h"
#include "user.h"
#include <glib.h>

#define INPUT_FILE "/users.csv"
#define ORDER_ASCENDING 1
#define ORDER_DESCENDING -1
#define ORDER_EQUAL 0

struct users {
    GHashTable *hash_table;
    GPtrArray *array;
};

static gint _user_comparator(gconstpointer user1, gconstpointer user2);

Users users_new(void)
{
    Users users = g_new(struct users, 1);

    users->hash_table =
        g_hash_table_new_full(g_str_hash, g_str_equal, (GDestroyNotify)g_free,
                              (GDestroyNotify)user_free);
    users->array = NULL;

    return users;
}

Users users_new_from_file(const char *inputs_path)
{
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
#pragma GCC diagnostic push

    return load_file(inputs_path, INPUT_FILE, users_new(), users_add_record);

#pragma GCC diagnostic pop
}

gboolean users_add_user(const Users users, const User u)
{
    return g_hash_table_insert(users->hash_table, user_get_username(u),
                               user_copy(u));
}

void users_add_record(const Users users, char *user_record)
{
    User user = user_new_from_record(user_record);
    if (user != NULL) {
        g_hash_table_insert(users->hash_table, user_get_username(user), user);
    }
}

User users_get_user(const Users users, const char *username)
{
    return user_copy(g_hash_table_lookup(users->hash_table, username));
}

guint users_size(const Users users)
{
    return users->array->len;
}

void users_add_user_ride_data(const Users users, const char *username,
                              guint8 score, double cost, guint16 date,
                              guint8 distance)
{
    user_add_ride_data(g_hash_table_lookup(users->hash_table, username), score,
                       cost, date, distance);
}

char users_get_user_gender(const Users users, const char *username)
{
    return user_get_gender(g_hash_table_lookup(users->hash_table, username));
}

guint16 users_get_user_account_age(const Users users, const char *username)
{
    return user_get_account_age(
        g_hash_table_lookup(users->hash_table, username));
}

int users_has_user(const Users users, const char *username)
{
    return g_hash_table_lookup(users->hash_table, username) != NULL;
}

Users users_list(const Users users)
{
    users->array = g_ptr_array_sized_new(g_hash_table_size(users->hash_table));

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, users->hash_table);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        g_ptr_array_add(users->array, value);
    }

    g_ptr_array_sort(users->array, (GCompareFunc)_user_comparator);

    return users;
}

GPtrArray *users_top_n_users(const Users users, guint N)
{
    GPtrArray *r = g_ptr_array_new_full(N, user_free);

    for (guint i = 0; i < users->array->len && i < N; i++) {
        g_ptr_array_add(r, user_copy(g_ptr_array_index(users->array, i)));
    }

    return r;
}

void users_free(const Users users)
{
    if (users != NULL) {
        if (users->hash_table != NULL) {
            g_hash_table_destroy(users->hash_table);
        }
        if (users->array != NULL) {
            g_ptr_array_free(users->array, TRUE);
        }
        g_free(users);
    }
}

static gint _user_comparator(gconstpointer a, gconstpointer b)
{
    const User u1 = *((User *)a);
    const User u2 = *((User *)b);

    const guint16 distance1 = user_get_total_distance(u1);
    const guint16 distance2 = user_get_total_distance(u2);

    if (distance1 < distance2)
        return ORDER_ASCENDING;
    else if (distance1 > distance2)
        return ORDER_DESCENDING;

    const guint16 ride_date1 = user_get_last_ride_date(u1);
    const guint16 ride_date2 = user_get_last_ride_date(u2);

    if (ride_date1 < ride_date2)
        return ORDER_ASCENDING;
    else if (ride_date1 > ride_date2)
        return ORDER_DESCENDING;

    char *username1 = user_get_username(u1);
    char *username2 = user_get_username(u2);

    const gint r = strcmp(username1, username2);

    free(username1);
    free(username2);

    return r;
}
