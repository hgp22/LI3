#include "query3.h"
#include "users.h"
#include "user.h"
#include <glib.h>

static gint _user_comparator(gconstpointer user1, gconstpointer user2);

Query3 new_query3(Users users)
{
    return (Query3)g_hash_table_get_values(users);
}

void free_query3(Query3 q3)
{
    g_slist_free(q3);
}

void free_query3_full(Query3 q3)
{
    g_slist_free_full(q3, free_user);
}

Query3 sort_query3(Query3 q3)
{
    return g_slist_sort(q3, (GCompareFunc)_user_comparator);
}

static gint _user_comparator(gconstpointer user1, gconstpointer user2)
{
    User u1 = (User)user1;
    User u2 = (User)user2;

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
