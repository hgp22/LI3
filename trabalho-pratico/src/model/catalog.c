#include "catalog.h"
#include "cities.h"
#include "driver.h"
#include "drivers.h"
#include "query2.h"
#include "query3.h"
#include "query8.h"
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
    Query8 query8;
};

Catalog catalog_new()
{
    return g_new(struct catalog, 1);
}

int catalog_process(Catalog c)
{
    rides_sort(c->rides);

    c->query8 = query8_new(c->rides, c->users, c->drivers);

    guint n_rides = c->rides->len;

    for (guint i = 0; i < n_rides; i++) {
        Ride r = rides_get_ride(c->rides, i);
        long d_id = ride_get_driver(r);
        Driver d = drivers_get_driver(c->drivers, d_id);
        ride_set_cost(r, d);
        driver_add_ride_data(d, r);
        char *username = ride_get_user(r);
        User u = users_get_user(c->users, username);
        free(username);
        user_add_ride_data(u, r);
        users_add_user(c->users, u);
        drivers_add_driver(c->drivers, d);
        rides_replace_ride(c->rides, r, i);
        user_free(u);
        driver_free(d);
        ride_free(r);
    }

    users_remove_inactive_accounts(c->users);
    drivers_remove_inactive_accounts(c->drivers);

    c->query2 = query2_new(c->drivers);
    query2_sort(c->query2);

    c->query3 = query3_new(c->users);
    query3_sort(c->query3);

    // query 4, 6 and 7
    c->cities = cities_new(c->rides, c->query2);

    return 0;
}

void catalog_free(Catalog c)
{
    users_free(c->users);
    drivers_free(c->drivers);
    rides_free(c->rides);
    query2_free(c->query2);
    query3_free(c->query3);
    cities_free(c->cities);
    free(c);
}

void catalog_set_users(Catalog c, Users users)
{
    c->users = users;
}

void catalog_set_drivers(Catalog c, Drivers drivers)
{
    c->drivers = drivers;
}

void catalog_set_rides(Catalog c, Rides rides)
{
    c->rides = rides;
}

User catalog_get_user(Catalog c, char *username)
{
    return users_get_user(c->users, username);
}

Driver catalog_get_driver(Catalog c, long id)
{
    return drivers_get_driver(c->drivers, id);
}

Query2 catalog_get_top_n_drivers_by_score(Catalog c, int N)
{
    Query2 r = query2_new_sized(N);

    for (int i = 0; i < N; i++) {
        query2_add_driver(r, driver_copy(query2_index(c->query2, i)));
    }

    return r;
}

Query3 catalog_get_top_n_users_by_distance(Catalog c, int N)
{
    Query3 r = query3_new_sized(N);

    for (int i = 0; i < N; i++) {
        query3_add_driver(r, user_copy(query3_index(c->query3, i)));
    }

    return r;
}

double catalog_get_city_avg_cost(Catalog c, char *city)
{
    return cities_get_city_avg_cost(c->cities, city);
}

double catalog_get_avg_cost_in_range(Catalog c, char *dateA, char *dateB)
{
    return rides_get_avg_stat_in_range(c->rides, dateA, dateB, ride_get_cost);
}

double catalog_get_city_avg_dist_in_range(Catalog c, char *city, char *dateA,
                                          char *dateB)
{
    return cities_get_city_avg_dist_in_range(c->cities, city, dateA, dateB);
}

Query2 catalog_get_top_n_drivers_in_city(Catalog c, char *city, int N)
{
    return cities_get_city_top_N_drivers(c->cities, city, N);
}
