#include "rides.h"
#include "ride.h"
#include <glib.h>

static gint _ride_comparator(gconstpointer ride1, gconstpointer ride2);

Rides insert_ride(Rides rides, Ride ride)
{
    return g_slist_prepend(rides, ride);
}

void free_rides(Rides rides)
{
    g_slist_free_full(rides, free_ride);
}

Rides sort_rides(Rides rides)
{
    return g_slist_sort(rides, (GCompareFunc)_ride_comparator);
}

static gint _ride_comparator(gconstpointer ride1, gconstpointer ride2)
{
    return get_ride_date((Ride)ride2) - get_ride_date((Ride)ride1);
}