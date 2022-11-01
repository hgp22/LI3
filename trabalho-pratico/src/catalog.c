#include "catalog.h"
#include "driver.h"
#include "drivers.h"
#include "inputs.h"
#include "parser_inputs.h"
#include "query2.h"
#include "query3.h"
#include "ride.h"
#include "rides.h"
#include "user.h"
#include "users.h"
#include <glib.h>

struct catalog {
    Users users;
    Drivers drivers;
    Rides rides;
    Query2 query2;
    Query3 query3;
};

Catalog init_catalog(Inputs i)
{
    Catalog c = g_new(struct catalog, 1);

    c->users = parse_users(get_inputs_users(i));
    c->drivers = parse_drivers(get_inputs_drivers(i));
    c->rides = parse_rides(get_inputs_rides(i));

    for (Rides iterator = c->rides; iterator; iterator = iterator->next) {
        long d_id = get_ride_driver(iterator->data); // ? use gint
        Driver d = get_driver(c->drivers, d_id);
        set_ride_cost(iterator->data, d);
        add_driver_ride_data(d, iterator->data);
        char *username = get_ride_user(iterator->data);
        User u = get_user(c->users, username);
        free(username);
        add_user_ride_data(u, iterator->data);
    }

    remove_inactive_users(c->users);
    remove_inactive_drivers(c->drivers);

    c->query2 = (Query2)g_hash_table_get_values(c->drivers);
    c->query2 = g_slist_sort(c->query2, (GCompareFunc)_driver_comparator);

    c->query3 = (Query3)g_hash_table_get_values(c->users);
    c->query3 = g_slist_sort(c->query3, (GCompareFunc)_user_comparator);

    return c;
}

void free_catalog(Catalog c)
{
    g_hash_table_destroy(g_steal_pointer(&c->users));
    g_hash_table_destroy(g_steal_pointer(&c->drivers));
    g_slist_free_full(c->rides, free_ride);
    g_slist_free(c->query2);
    g_slist_free(c->query3);
    free(c);
}

Users get_catalog_users(Catalog c)
{
    return c->users;
}

Drivers get_catalog_drivers(Catalog c)
{
    return c->drivers;
}

Rides get_catalog_rides(Catalog c)
{
    return c->rides;
}

Query2 get_catalog_query2(Catalog c)
{
    return c->query2;
}

Query3 get_catalog_query3(Catalog c)
{
    return c->query3;
}

User get_catalog_user(Catalog c, char *username)
{
    return get_user(c->users, username);
}

Driver get_catalog_driver(Catalog c, long id)
{
    return get_driver(c->drivers, id);
}

static gint _driver_comparator(gconstpointer driver1, gconstpointer driver2)
{
    Driver d1 = (Driver)driver1;
    Driver d2 = (Driver)driver2;

    float score1 = get_driver_avg_score(d1);
    float score2 = get_driver_avg_score(d2);

    if (score1 < score2)
        return 1;
    else if (score1 > score2)
        return -1;
    else {
        unsigned short ride_date1 = get_driver_last_ride_date(d1);
        unsigned short ride_date2 = get_driver_last_ride_date(d2);

        if (ride_date1 < ride_date2)
            return 1;
        else if (ride_date1 > ride_date2)
            return -1;
        else {
            long id1 = get_driver_id(d1);
            long id2 = get_driver_id(d2);

            if (id1 < id2)
                return 1;
            else if (id1 > id2)
                return -1;
            else
                return 0;
        }
    }
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
