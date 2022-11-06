#include "query4.h"
#include "ride.h"
#include "rides.h"
#include <glib.h>

struct city {
    Rides rides;
    double sum_costs;
    int n_rides;
};

static void _key_destroyed(gpointer data);
static void _value_destroyed(gpointer data);

Query4 new_query4(void)
{
    return g_hash_table_new_full(g_str_hash, g_str_equal,
                                 (GDestroyNotify)_key_destroyed,
                                 (GDestroyNotify)_value_destroyed);
}

void free_query4(Query4 q4)
{
    g_hash_table_destroy(g_steal_pointer(&q4));
}

void add_query4_ride(Query4 q4, Ride r)
{
    double cost = get_ride_cost(r);
    char *city = get_ride_city(r);
    City found = g_hash_table_lookup(q4, city);
    if (found != NULL) {
        g_array_append_val(found->rides, r);
        found->sum_costs += cost;
        found->n_rides++;
        free(city);
    }
    else {
        City new = g_new(struct city, 1);
        new->rides = g_array_new(FALSE, FALSE, sizeof(Ride));
        g_array_append_val(new->rides, r);
        new->sum_costs = cost;
        new->n_rides = 1;
        g_hash_table_insert(q4, city, new);
    }
}

double get_query4_city_avg_cost(Query4 q4, char *city)
{
    City c = g_hash_table_lookup(q4, city);
    return c->sum_costs / c->n_rides;
}

double avg_distance(Query4 q4, char *city, char *dateA, char *dateB)
{
    City c = g_hash_table_lookup(q4, city);
    return get_rides_avg_distance_in_range(c->rides, dateA, dateB);
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
