#include "query8.h"
#include "driver.h"
#include "drivers.h"
#include "ride.h"
#include "rides.h"
#include "user.h"
#include "users.h"
#include "utils.h"
#include <glib.h>
#include <stdio.h>

#define RESERVED 262144 // (2^18)

struct query8 {
    Rides female;
    Rides male;
};

static gint _ride_comparator(gconstpointer a, gconstpointer b);

Query8 query8_new(Rides rides, Users users, Drivers drivers)
{
    Query8 q8 = g_new(struct query8, 1);

    q8->female = g_ptr_array_sized_new(RESERVED);
    q8->male = g_ptr_array_sized_new(RESERVED);

    for (guint i = 0; i < rides->len; i++) {
        Ride r = g_ptr_array_index(rides, i);
        long d_id = ride_get_driver(r);
        Driver d = drivers_get_driver(drivers, d_id);
        if (d == NULL) {
            continue;
        }
        char *username = ride_get_user(r);
        User u = users_get_user(users, username);
        if (u == NULL) {
            driver_free(d);
            free(username);
            continue;
        }
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

    g_ptr_array_sort(q8->female, (GCompareFunc)_ride_comparator);
    g_ptr_array_sort(q8->male, (GCompareFunc)_ride_comparator);

    return q8;
}

void query8_free(Query8 q8)
{
    g_ptr_array_free(q8->female, TRUE);
    g_ptr_array_free(q8->male, TRUE);
    g_free(q8);
}

Rides query8_get_answer(Query8 q8, char gender, int account_age)
{
    char date[18];
    snprintf(date, 18, "09/10/%d", 2022 - account_age);
    unsigned short age_days = date_to_days(date);

    Rides rides;

    switch (gender) {
        case 'F':
            rides = q8->female;
            break;
        case 'M':
            rides = q8->male;
            break;
        default:
            return NULL;
    }

    Rides answer = g_ptr_array_new_with_free_func((GDestroyNotify)ride_free);

    guint i = 0;
    for (Ride r = g_ptr_array_index(rides, i);
         i < rides->len && ride_get_driver_account_age(r) <= age_days;
         r = g_ptr_array_index(rides, ++i)) {
        if (ride_get_user_account_age(r) <= age_days) {
            g_ptr_array_add(answer, ride_copy(r));
        }
    }

    return answer;
}

static gint _ride_comparator(gconstpointer a, gconstpointer b)
{
    const Ride r1 = *((Ride *)a);
    const Ride r2 = *((Ride *)b);

    unsigned short d_account_age1 = ride_get_driver_account_age(r1);
    unsigned short d_account_age2 = ride_get_driver_account_age(r2);

    if (d_account_age1 < d_account_age2) {
        return -1;
    }
    else if (d_account_age1 > d_account_age2) {
        return 1;
    }
    else {
        unsigned short u_account_age1 = ride_get_user_account_age(r1);
        unsigned short u_account_age2 = ride_get_user_account_age(r2);

        if (u_account_age1 < u_account_age2) {
            return -1;
        }
        else if (u_account_age1 > u_account_age2) {
            return 1;
        }
        else {
            long id1 = ride_get_id(r1);
            long id2 = ride_get_id(r2);

            if (id1 < id2) {
                return -1;
            }
            else if (id1 > id2) {
                return 1;
            }
            else {
                return 0;
            }
        }
    }
}
