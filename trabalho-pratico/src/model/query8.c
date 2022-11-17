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

/*
typedef struct people {
    Users users;
    Drivers drivers;
} * People;
*/

// static gint _ride_comparator(gconstpointer a, gconstpointer b, gpointer user_data);
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

    /*
    People people = g_new(struct people, 1);
    people->users = users;
    people->drivers = drivers;

    g_ptr_array_sort_with_data(q8->female, _ride_comparator, people);
    g_ptr_array_sort_with_data(q8->male, _ride_comparator, people);
    */

    g_ptr_array_sort(q8->female, _ride_comparator);
    g_ptr_array_sort(q8->male, _ride_comparator);

    // g_free(people);

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
         i < rides->len && ride_get_driver_account_age(r) >= account_age;
         r = g_ptr_array_index(rides, ++i)) {
        if (ride_get_user_account_age(r) >= account_age) {
            g_ptr_array_add(answer, r);
        }
    }

    return answer;
}

// static gint _ride_comparator(gconstpointer a, gconstpointer b,
static gint _ride_comparator(gconstpointer a, gconstpointer b)
{
    // People people = (People)user_data;
    // Drivers drivers = people->drivers;

    const Ride r1 = *((Ride *)a);
    const Ride r2 = *((Ride *)b);

    // long d_id1 = ride_get_driver(r1);
    // // Driver d1 = drivers_get_driver(drivers, d_id1);
    // Driver d1 = g_hash_table_lookup(drivers, &d_id1);
    // unsigned short d_account_age1 = driver_get_account_age(d1);
    // // driver_free(d1);

    // long d_id2 = ride_get_driver(r2);
    // // Driver d2 = drivers_get_driver(drivers, d_id2);
    // Driver d2 = g_hash_table_lookup(drivers, &d_id2);
    // unsigned short d_account_age2 = driver_get_account_age(d2);
    // // driver_free(d2);

    unsigned short d_account_age1 = ride_get_driver_account_age(r1);
    unsigned short d_account_age2 = ride_get_driver_account_age(r2);

    if (d_account_age1 < d_account_age2) {
        return -1;
    }
    else if (d_account_age1 > d_account_age2) {
        return 1;
    }
    else {
        // Users users = people->users;

        // char *username1 = ride_get_user(r1);
        // // User u1 = users_get_user(users, username1);
        // User u1 = g_hash_table_lookup(users, username1);
        // free(username1);
        // unsigned short u_account_age1 = user_get_account_age(u1);
        // // user_free(u1);

        // char *username2 = ride_get_user(r2);
        // // User u2 = users_get_user(users, username2);
        // User u2 = g_hash_table_lookup(users, username2);
        // free(username2);
        // unsigned short u_account_age2 = user_get_account_age(u2);
        // // user_free(u2);

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

            if (id1 < id2)
                return -1;
            else if (id1 > id2)
                return 1;
            else
                return 0;
        }
    }
}
