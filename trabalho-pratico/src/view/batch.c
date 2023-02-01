#include "view/batch.h"
#include "date.h"
#include "driver.h"
#include "ride.h"
#include "taxi_system.h"
#include "user.h"
#include <stdio.h>

void batch_print_query1_user(const User u, FILE *fp)
{
    if (u != NULL) {
        char *name = user_get_name(u);
        fprintf(fp, "%s;%c;%d;%.3f;%hu;%.3f\n", name, user_get_gender(u),
                user_get_age(u), user_get_avg_score(u), user_get_n_trips(u),
                user_get_total_spent(u));
        free(name);
    }
}

void batch_print_query1_driver(const Driver d, FILE *fp)
{
    if (d != NULL) {
        char *name = driver_get_name(d);
        fprintf(fp, "%s;%c;%d;%.3f;%hu;%.3f\n", name, driver_get_gender(d),
                driver_get_age(d), driver_get_avg_score(d),
                driver_get_n_trips(d), driver_get_total_earned(d));
        free(name);
    }
}

void batch_print_query2(const GPtrArray *drivers, FILE *fp)
{
    for (guint i = 0; i < drivers->len; i++) {
        Driver d = (Driver)g_ptr_array_index(drivers, i);
        char *name = driver_get_name(d);
        fprintf(fp, "%012d;%s;%.3f\n", driver_get_id(d), name,
                driver_get_avg_score(d));
        free(name);
    }
}

void batch_print_query3(const GPtrArray *users, FILE *fp)
{
    for (guint i = 0; i < users->len; i++) {
        User u = (User)g_ptr_array_index(users, i);
        char *name = user_get_name(u);
        char *username = user_get_username(u);
        fprintf(fp, "%s;%s;%d\n", username, name, user_get_total_distance(u));
        free(username);
        free(name);
    }
}

void batch_print_query4(double avg_score, FILE *fp)
{
    fprintf(fp, "%.3f\n", avg_score);
}

void batch_print_query5(double avg_cost, FILE *fp)
{
    fprintf(fp, "%.3f\n", avg_cost);
}

void batch_print_query6(double avg_distance, FILE *fp)
{
    fprintf(fp, "%.3f\n", avg_distance);
}

void batch_print_query7(const GPtrArray *drivers, const char *city, FILE *fp)
{
    for (guint i = 0; i < drivers->len; i++) {
        Driver d = (Driver)g_ptr_array_index(drivers, i);
        char *name = driver_get_name(d);
        fprintf(fp, "%012d;%s;%.3f\n", driver_get_id(d), name,
                driver_get_city_score(d, city));
        free(name);
    }
}

void batch_print_query8(const GPtrArray *rides, const TaxiSystem ts, FILE *fp)
{
    for (guint i = 0; i < rides->len; i++) {
        Ride r = g_ptr_array_index(rides, i);
        char *user = ride_get_user(r);
        int driver = ride_get_driver(r);
        User u = taxi_get_user(ts, user);
        free(user);
        Driver d = taxi_get_driver(ts, driver);
        char *user_name = user_get_name(u);
        char *user_username = user_get_username(u);
        user_free(u);
        char *driver_name = driver_get_name(d);
        fprintf(fp, "%012d;%s;%s;%s\n", driver_get_id(d), driver_name,
                user_username, user_name);
        driver_free(d);
        free(user_name);
        free(user_username);
        free(driver_name);
    }
}

void batch_print_query9(const GPtrArray *rides, FILE *fp)
{
    for (guint i = 0; i < rides->len; i++) {
        Ride r = (Ride)g_ptr_array_index(rides, i);
        char *date = days_to_date(ride_get_date(r));
        char *city = ride_get_city(r);
        fprintf(fp, "%012d;%s;%d;%s;%.3f\n", ride_get_id(r), date,
                (int)ride_get_distance(r), city, ride_get_tip(r));
        free(date);
        free(city);
    }
}
