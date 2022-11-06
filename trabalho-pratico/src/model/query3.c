#include "query3.h"
#include "user.h"
#include "users.h"
#include <glib.h>

static gint _user_comparator(gconstpointer user1, gconstpointer user2);

Query3 new_query3(Users users)
{
    Query3 q3 = g_ptr_array_sized_new(g_hash_table_size(users));
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, users);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        g_ptr_array_add(q3, value);
    }
    return q3;
}

void free_query3(Query3 q3)
{
    g_ptr_array_free(q3, TRUE);
}

void sort_query3(Query3 q3)
{
    g_ptr_array_sort(q3, (GCompareFunc)_user_comparator);
}

static gint _user_comparator(gconstpointer a, gconstpointer b)
{
    User u1 = *((User *)a);
    User u2 = *((User *)b);

    unsigned short distance1 = get_user_total_distance(u1);
    unsigned short distance2 = get_user_total_distance(u2);

    if (distance1 < distance2)
        return 1;
    else if (distance1 > distance2)
        return -1;
    else {
        unsigned short ride_date1 = get_user_last_ride_date(u1);
        unsigned short ride_date2 = get_user_last_ride_date(u2);

        if (ride_date1 < ride_date2)
            return 1;
        else if (ride_date1 > ride_date2)
            return -1;
        else {
            char *username1 = get_user_username(u1);
            char *username2 = get_user_username(u2);

            int r = strcmp(username1, username2);

            free(username1);
            free(username2);

            return r;
        }
    }
}
