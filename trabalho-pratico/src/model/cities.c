#include "cities.h"
#include "ride.h"
#include "rides.h"
#include <glib.h>

#define RESERVED_SIZE 262144 // (2^18)

typedef struct city {
    Rides rides;
    double sum_costs;
    int n_rides;
} * City;

static void _key_destroyed(gpointer data);
static void _value_destroyed(gpointer data);

Cities new_cities(void)
{
    return g_hash_table_new_full(g_str_hash, g_str_equal,
                                 (GDestroyNotify)_key_destroyed,
                                 (GDestroyNotify)_value_destroyed);
}

void free_cities(Cities cities)
{
    g_hash_table_destroy(g_steal_pointer(&cities));
}

void add_cities_ride(Cities cities, Ride r)
{
    double cost = get_ride_cost(r);
    char *city = get_ride_city(r);
    City found = g_hash_table_lookup(cities, city);
    if (found != NULL) {
        g_array_append_val(found->rides, r);
        found->sum_costs += cost;
        found->n_rides++;
        free(city);
    }
    else {
        City new = g_new(struct city, 1);
        new->rides =
            g_array_sized_new(FALSE, FALSE, sizeof(Ride), RESERVED_SIZE);
        g_array_append_val(new->rides, r);
        new->sum_costs = cost;
        new->n_rides = 1;
        g_hash_table_insert(cities, city, new);
    }
}

double get_cities_city_avg_cost(Cities cities, char *city)
{
    City c = g_hash_table_lookup(cities, city);
    return c->sum_costs / c->n_rides;
}

double get_cities_city_avg_dist_in_range(Cities cities, char *city, char *dateA,
                                         char *dateB)
{
    City c = g_hash_table_lookup(cities, city);
    return get_rides_avg_stat_in_range(c->rides, dateA, dateB,
                                       get_ride_distance);
}

static void _key_destroyed(gpointer data)
{
    g_free(data);
}

static void _value_destroyed(gpointer data)
{
    City city = (City)data;
    g_array_free(city->rides, TRUE);
    g_free(data);
}
