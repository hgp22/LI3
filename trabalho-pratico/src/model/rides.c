#include "rides.h"
#include "ride.h"
#include <glib.h>

static gint _ride_comparator(gconstpointer ride1, gconstpointer ride2);

Rides new_rides(void)
{
    return g_ptr_array_new_with_free_func(free_ride);
}

void add_ride(Rides rides, Ride ride)
{
    g_ptr_array_add(rides, (gpointer)ride);
}

void free_rides(Rides rides)
{
    g_ptr_array_free(rides, TRUE);
}

void sort_rides(Rides rides)
{
    g_ptr_array_sort(rides, (GCompareFunc)_ride_comparator);
}

static gint _ride_comparator(gconstpointer a, gconstpointer b)
{
    const Ride r1 = *((Ride *)a);
    const Ride r2 = *((Ride *)b);
    return get_ride_date(r1) - get_ride_date(r2);
}
