#include "taxi_system.h"
#include "driver.h"
#include "drivers.h"
#include "ride.h"
#include "rides.h"
#include "user.h"
#include "users.h"
#include "validation.h"
#include <glib.h>

struct taxi_system {
    Users users;
    Drivers drivers;
    Rides rides;
};

static TaxiSystem _taxi_process(const TaxiSystem ts);
static void _correlate_collections(Rides rides, Users users, Drivers drivers);

TaxiSystem taxi_new(const char *inputs_path)
{
    TaxiSystem ts = g_new(struct taxi_system, 1);
    compile_regex();
    ts->users = users_new_from_file(inputs_path);
    ts->drivers = drivers_new_from_file(inputs_path);
    ts->rides = rides_new_from_file(inputs_path);
    free_regex();
    _taxi_process(ts);
    return ts;
}

static TaxiSystem _taxi_process(const TaxiSystem ts)
{
    // Query 5
    rides_sort_date(ts->rides);

    _correlate_collections(ts->rides, ts->users, ts->drivers);

    rides_sort_accounts_age(ts->rides);

    // query 3
    users_list(ts->users);

    // query 2
    drivers_process(ts->drivers);

    // queries 4 and 6
    rides_cities(ts->rides);

    // query 7
    drivers_cities(ts->drivers);

    // query 9
    rides_with_tip(ts->rides);

    return ts;
}

User taxi_get_user(const TaxiSystem ts, const char *username)
{
    return users_get_user(ts->users, username);
}

Driver taxi_get_driver(const TaxiSystem ts, int id)
{
    return drivers_get_driver(ts->drivers, id);
}

GPtrArray *taxi_top_n_drivers_by_score(const TaxiSystem ts, int N)
{
    return drivers_top_n_drivers(ts->drivers, N);
}

GPtrArray *taxi_top_n_users_by_distance(const TaxiSystem ts, int N)
{
    return users_top_n_users(ts->users, N);
}

double taxi_city_avg_cost(const TaxiSystem ts, const char *city)
{
    return rides_city_avg_cost(ts->rides, city);
}

double taxi_avg_cost_in_range(const TaxiSystem ts, const char *dateA,
                              const char *dateB)
{
    return rides_get_avg_cost_in_range(ts->rides, dateA, dateB);
}

double taxi_city_avg_dist_in_range(const TaxiSystem ts, const char *city,
                                   const char *dateA, const char *dateB)
{
    return rides_city_avg_dist_in_range(ts->rides, city, dateA, dateB);
}

GPtrArray *taxi_top_n_drivers_in_city(const TaxiSystem ts, const char *city,
                                      int N)
{
    return drivers_top_n_drivers_in_city(ts->drivers, city, N);
}

GPtrArray *taxi_query8(const TaxiSystem ts, char gender, int account_age)
{
    return rides_by_gender_by_age(ts->rides, gender, account_age);
}

GPtrArray *taxi_rides_with_tip_in_range(const TaxiSystem ts, const char *dateA,
                                        const char *dateB)
{
    return rides_get_rides_with_tip_in_range(ts->rides, dateA, dateB);
}

void taxi_free(const TaxiSystem ts)
{
    users_free(ts->users);
    drivers_free(ts->drivers);
    rides_free(ts->rides);
    free(ts);
}

static void _correlate_collections(const Rides rides, const Users users,
                                   const Drivers drivers)
{
    const double base[] = {3.25, 4.00, 5.20};
    const double tax[] = {0.62, 0.79, 0.94};

    rides_new_genders(rides);

    for (guint i = 0; i < rides_size(rides); i++) {
        int driver_id = rides_get_ride_driver(rides, i);
        CarClass car_class = drivers_get_driver_car_class(drivers, driver_id);
        guint8 distance = rides_get_ride_distance(rides, i);
        double cost = base[car_class] + tax[car_class] * distance;
        rides_set_ride_cost(rides, i, cost);
        cost += rides_get_ride_tip(rides, i);
        guint16 date = rides_get_ride_date(rides, i);
        char *username = rides_get_ride_user(rides, i);

        char driver_exists, user_exists;

        if ((driver_exists = drivers_is_driver_active(drivers, driver_id))) {
            rides_set_ride_driver_account_age(
                rides, i, drivers_get_driver_account_age(drivers, driver_id));
            char *city = rides_get_ride_city(rides, i);
            drivers_add_driver_ride_data(drivers, driver_id,
                                         rides_get_ride_score_driver(rides, i),
                                         cost, date, city);
            free(city);
        }

        if ((user_exists = users_has_user(users, username))) {
            rides_set_ride_user_account_age(
                rides, i, users_get_user_account_age(users, username));
            users_add_user_ride_data(users, username,
                                     rides_get_ride_score_user(rides, i), cost,
                                     date, distance);
        }

        if (!user_exists || !driver_exists) {
            free(username);
            continue;
        }

        char driver_gender = drivers_get_driver_gender(drivers, driver_id);
        char user_gender = users_get_user_gender(users, username);
        free(username);

        if (user_gender == driver_gender) {
            switch (user_gender) {
                case 'F':
                    rides_add_females_ride_index(rides, i);
                    break;
                case 'M':
                    rides_add_males_ride_index(rides, i);
                    break;
            }
        }
    }
}
