#include "query8.h"
#include "driver.h"
#include "drivers.h"
#include "ride.h"
#include "rides.h"
#include "user.h"
#include "users.h"
#include <glib.h>

#define RESERVED 262144 // (2^18)

struct query8 {
    Rides female;
    Rides male;
};

Query8 query8_new(Rides rides, Users users, Drivers drivers)
{
    Query8 q8 = g_new(struct query8, 1);

    q8->female = g_ptr_array_sized_new(RESERVED);
    q8->male = g_ptr_array_sized_new(RESERVED);

    for (guint i = 0; i < rides->len; i++) {
        Ride r = g_ptr_array_index(rides, i);
        long d_id = ride_get_driver(r);
        Driver d = drivers_get_driver(drivers, d_id);
        char *username = ride_get_user(r);
        User u = users_get_user(users, username);
        free(username);

        char user_gender = user_get_gender(u);
        char driver_gender = driver_get_gender(d);

        if (user_gender == driver_gender) {
            switch (user_gender) {
                case 'F':
                    g_ptr_array_add(q8->female, r);
                    break;
                case 'M':
                    g_ptr_array_add(q8->male, r);
                    break;
            }
        }

        user_free(u);
        driver_free(d);
    }

    return q8;
}
