#include "catalog.h"
#include "driver.h"
#include "drivers.h"
#include "query2.h"
#include "query3.h"
#include "query4.h"
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
    Query4 query4;
};

Catalog new_catalog()
{
    Catalog c = g_new(struct catalog, 1);
    c->query4 = new_query4();
    return c;
}

int process_catalog(Catalog c)
{
    for (Rides iterator = c->rides; iterator; iterator = iterator->next) {
        Ride r = iterator->data;
        long d_id = get_ride_driver(r);
        Driver d = get_driver(c->drivers, d_id);
        set_ride_cost(r, d);
        add_driver_ride_data(d, r);
        char *username = get_ride_user(r);
        User u = get_users_user(c->users, username);
        free(username);
        add_user_ride_data(u, r);
        double cost = get_ride_cost(r);
        char *city = get_ride_city(r);
        add_query4_ride_cost(c->query4, city, cost);
    }

    remove_inactive_users(c->users);
    remove_inactive_drivers(c->drivers);

    c->query2 = new_query2(c->drivers);
    c->query2 = sort_query2(c->query2);

    c->query3 = new_query3(c->users);
    c->query3 = sort_query3(c->query3);

    return 0;
}

void free_catalog(Catalog c)
{
    free_users(c->users);
    free_drivers(c->drivers);
    free_rides(c->rides);
    free_query2(c->query2);
    free_query3(c->query3);
    free_query4(c->query4);
    free(c);
}

void set_catalog_users(Catalog c, Users users)
{
    c->users = users;
}

void set_catalog_drivers(Catalog c, Drivers drivers)
{
    c->drivers = drivers;
}

void set_catalog_rides(Catalog c, Rides rides)
{
    c->rides = rides;
}

Rides get_catalog_rides(Catalog c)
{
    return c->rides;
}

Query2 get_catalog_top_n_drivers_by_score(Catalog c, int N)
{
    Query2 r = NULL;

    for (Query2 itr = c->query2; itr && N; itr = itr->next, N--) {
        r = g_slist_prepend(r, copy_driver(itr->data));
    }

    return g_slist_reverse(r);
}

Query3 get_catalog_top_n_users_by_distance(Catalog c, int N)
{
    Query3 r = NULL;

    for (Query3 itr = c->query3; itr && N; itr = itr->next, N--) {
        r = g_slist_prepend(r, copy_user(itr->data));
    }

    return g_slist_reverse(r);
}

double get_catalog_city_avg_cost(Catalog c, char *city)
{
    return get_query4_city_avg_cost(c->query4, city);
}

User get_catalog_user(Catalog c, char *username)
{
    return copy_user(get_users_user(c->users, username));
}

Driver get_catalog_driver(Catalog c, long id)
{
    return copy_driver(get_driver(c->drivers, id));
}
