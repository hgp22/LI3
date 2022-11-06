#include "catalog.h"
#include "cities.h"
#include "driver.h"
#include "drivers.h"
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
    Cities cities;
};

Catalog new_catalog()
{
    Catalog c = g_new(struct catalog, 1);
    c->cities = new_cities();
    return c;
}

int process_catalog(Catalog c)
{
    sort_rides(c->rides);

    guint n_rides = c->rides->len;

    for (guint i = 0; i < n_rides; i++) {
        Ride r = get_rides_ride(c->rides, i);
        long d_id = get_ride_driver(r);
        Driver d = get_drivers_driver(c->drivers, d_id);
        set_ride_cost(r, d);
        add_driver_ride_data(d, r);
        char *username = get_ride_user(r);
        User u = get_users_user(c->users, username);
        free(username);
        add_user_ride_data(u, r);
        add_cities_ride(c->cities, r);
    }

    remove_inactive_users(c->users);
    remove_inactive_drivers(c->drivers);

    c->query2 = new_query2(c->drivers);
    sort_query2(c->query2);

    c->query3 = new_query3(c->users);
    sort_query3(c->query3);

    return 0;
}

void free_catalog(Catalog c)
{
    free_users(c->users);
    free_drivers(c->drivers);
    free_rides(c->rides);
    free_query2(c->query2);
    free_query3(c->query3);
    free_cities(c->cities);
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

User get_catalog_user(Catalog c, char *username)
{
    return copy_user(get_users_user(c->users, username));
}

Driver get_catalog_driver(Catalog c, long id)
{
    return copy_driver(get_drivers_driver(c->drivers, id));
}

Query2 get_catalog_top_n_drivers_by_score(Catalog c, int N)
{
    Query2 r = g_ptr_array_new_full(N, free_driver);

    for (int i = 0; i < N; i++) {
        g_ptr_array_add(r, copy_driver(g_ptr_array_index(c->query2, i)));
    }

    return r;
}

Query3 get_catalog_top_n_users_by_distance(Catalog c, int N)
{
    Query3 r = g_ptr_array_new_full(N, free_user);

    for (int i = 0; i < N; i++) {
        g_ptr_array_add(r, copy_user(g_ptr_array_index(c->query3, i)));
    }

    return r;
}

double get_catalog_city_avg_cost(Catalog c, char *city)
{
    return get_cities_city_avg_cost(c->cities, city);
}

double get_catalog_avg_cost_in_range(Catalog c, char *dateA, char *dateB)
{
    return get_rides_avg_stat_in_range(c->rides, dateA, dateB, get_ride_cost);
}

double get_catalog_city_avg_dist_in_range(Catalog c, char *city, char *dateA,
                                          char *dateB)
{
    return get_cities_city_avg_dist_in_range(c->cities, city, dateA, dateB);
}
