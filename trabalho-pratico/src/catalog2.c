#include "catalog2.h"
#include "query1.h"
#include <glib.h>

struct catalog2 {
    GHashTable *query1;
};

Catalog2 init_catalog2(Catalog c)
{
    Catalog2 c2 = g_new(struct catalog2, 1);
    /*
        c2->query1 = g_hash_table_new(g_str_hash, g_str_equal);

        g_slist_foreach(get_catalog_users(c), (GFunc)insert_user_hash,
       c2->query1);

        printf("%s\n",
               query1_to_string(g_hash_table_lookup(c2->query1, "MiTeixeira")));

        g_slist_foreach(get_catalog_rides(c), (GFunc)update_query1, c2->query1);

        printf("%s\n",
               query1_to_string(g_hash_table_lookup(c2->query1, "MiTeixeira")));
    */
    return c2;
}

void insert_user_hash(gpointer user, gpointer query1)
{
    Query1 q1 = init_query1(user);
    g_hash_table_insert(query1, get_user_username(user), q1);
}

void update_query1(gpointer ride, gpointer query1)
{
    // Query1 q1 = g_hash_table_lookup(query1, get_ride_user(ride));

    // add_score(q1, get_ride_score_user(ride));
}