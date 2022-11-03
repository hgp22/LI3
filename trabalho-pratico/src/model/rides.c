#include "rides.h"
#include "ride.h"

Rides insert_ride(Rides rides, Ride ride)
{
    return g_slist_prepend(rides, ride);
}

void free_rides(Rides rides)
{
    g_slist_free_full(rides, free_ride);
}
