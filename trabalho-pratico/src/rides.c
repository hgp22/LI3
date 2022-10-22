#include "rides.h"
#include "ride.h"

Rides *insert_ride(Rides *rides, Ride ride)
{
    return g_slist_prepend(rides, ride);
}
