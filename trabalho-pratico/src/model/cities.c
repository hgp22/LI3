#include "cities.h"
#include "driver.h"
#include "drivers.h"
#include "query2.h"
#include "ride.h"
#include "rides.h"
#include <glib.h>

#define RESERVED_RIDES 262144 // (2^18)

typedef struct city {
    Rides rides;
    Query2 drivers;
    double sum_costs;
    int n_rides;
} * City;

static gint _sort_drivers_by_city(gconstpointer a, gconstpointer b,
                                  gpointer user_data);
static void _key_destroyed(gpointer data);
static void _value_destroyed(gpointer data);

Cities cities_new(Rides rides, Query2 drivers)
{
    Cities cities = g_hash_table_new_full(g_str_hash, g_str_equal,
                                          (GDestroyNotify)_key_destroyed,
                                          (GDestroyNotify)_value_destroyed);

    // add rides to cities
    for (guint i = 0; i < rides->len; i++) {
        Ride r = rides_get_ride_shallow(rides, i);
        double cost = ride_get_cost(r);
        char *city = ride_get_city(r);
        City found = g_hash_table_lookup(cities, city);
        if (found != NULL) {
            g_ptr_array_add(found->rides, r);
            found->sum_costs += cost;
            found->n_rides++;
            free(city);
        }
        else {
            City new = g_new(struct city, 1);
            new->rides = g_ptr_array_sized_new(RESERVED_RIDES);
            new->drivers = g_ptr_array_sized_new(drivers->len);
            g_ptr_array_add(new->rides, r);
            new->sum_costs = cost;
            new->n_rides = 1;
            g_hash_table_insert(cities, city, new);
        }
    }

    // add drivers to cities
    for (guint i = 0; i < drivers->len; i++) {
        Driver d = g_ptr_array_index(drivers, i);
        CitiesScore cities_score = driver_get_cities_score(d);
        GHashTableIter iter;
        gpointer key, value;
        g_hash_table_iter_init(&iter, cities_score);
        while (g_hash_table_iter_next(&iter, &key, &value)) {
            City city = g_hash_table_lookup(cities, key);
            g_ptr_array_add(city->drivers, d);
        }
        driver_free_cities_score(cities_score);
    }

    // sort drivers in cities by driver score in city
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, cities);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        City city = (City)value;
        g_ptr_array_sort_with_data(city->drivers, _sort_drivers_by_city, key);
    }

    return cities;
}

void cities_free(Cities cities)
{
    g_hash_table_destroy(g_steal_pointer(&cities));
}

double cities_get_city_avg_cost(Cities cities, char *city)
{
    City c = g_hash_table_lookup(cities, city);
    return c->sum_costs / c->n_rides;
}

double cities_get_city_avg_dist_in_range(Cities cities, char *city, char *dateA,
                                         char *dateB)
{
    City c = g_hash_table_lookup(cities, city);
    return rides_get_avg_stat_in_range(c->rides, dateA, dateB,
                                       ride_get_distance);
}

Query2 cities_get_city_top_N_drivers(Cities cities, char *city, int N)
{
    City c = g_hash_table_lookup(cities, city);
    Query2 r = query2_new_sized(N);

    for (int i = 0; i < N; i++) {
        query2_add_driver(r, driver_copy(g_ptr_array_index(c->drivers, i)));
    }

    return r;
}

static gint _sort_drivers_by_city(gconstpointer a, gconstpointer b,
                                  gpointer user_data)
{
    Driver d1 = *((Driver *)a);
    Driver d2 = *((Driver *)b);
    char *city = (char *)user_data;

    double avg_score1 = driver_get_city_score(d1, city);
    double avg_score2 = driver_get_city_score(d2, city);

    if (avg_score1 < avg_score2) {
        return 1;
    }
    else if (avg_score1 > avg_score2) {
        return -1;
    }
    else {
        return driver_get_id(d2) - driver_get_id(d1);
    }
}

static void _key_destroyed(gpointer data)
{
    g_free(data);
}

static void _value_destroyed(gpointer data)
{
    City city = (City)data;
    g_ptr_array_free(city->rides, TRUE);
    g_ptr_array_free(city->drivers, TRUE);
    g_free(data);
}
