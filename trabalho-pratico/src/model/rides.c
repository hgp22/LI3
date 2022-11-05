#include "rides.h"
#include "ride.h"
#include <glib.h>

#define RESERVED_SIZE 1048576 // (2^20)

static gint _ride_comparator(gconstpointer ride1, gconstpointer ride2);

Rides new_rides(void)
{
    Rides r = g_array_sized_new(FALSE, FALSE, sizeof(Ride), RESERVED_SIZE);
    g_array_set_clear_func (r, (GDestroyNotify)free_ride);
    return r;
}

void add_ride(Rides rides, Ride ride)
{
    g_array_append_val(rides, ride);
}

void free_rides(Rides rides)
{
    g_array_free(rides, TRUE);
}

void sort_rides(Rides rides)
{
    g_array_sort(rides, (GCompareFunc)_ride_comparator);
}

static gint _ride_comparator(gconstpointer a, gconstpointer b)
{
    const Ride r1 = (Ride)a;
    const Ride r2 = (Ride)b;
    return get_ride_date(r1) - get_ride_date(r2);
}
