#include "query9.h"
#include "rides.h"
#include "ride.h"

Query9 query9_new(Rides rides)
{
    Query9 q9 = g_ptr_array_sized_new(rides->len);

    for (guint i = 0; i < rides->len; i++) {
        Ride r = rides_get_ride_shallow(rides, i);
        if (ride_get_tip(r) != 0) {
            g_ptr_array_add(q9, r);
        }
    }

    return q9;
}
