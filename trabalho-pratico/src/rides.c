#include "rides.h"
#include "rides.h"

Rides *insert_ride(Rides *rides, Ride *ride)
{
    return g_slist_prepend(rides, ride);
}
