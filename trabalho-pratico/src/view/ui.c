#include "ui.h"
#include "driver.h"
#include "query2.h"
#include "query3.h"
#include "query9.h"
#include "ride.h"
#include "user.h"
#include "utils.h"
#include <stdio.h>

static int counter = 1;

FILE *next_output_file(void)
{
    char file[64];
    sprintf(file, "./Resultados/command%d_output.txt", counter++);
    return freopen(file, "w", stdout);
}

void show_query1_user(User u)
{
    if (u != NULL) {
        char *name = user_get_name(u);
        printf("%s;%c;%d;%.3f;%hu;%.3f\n", name, user_get_gender(u),
               user_get_age(u), user_get_avg_score(u), user_get_n_trips(u),
               user_get_total_spent(u));
        free(name);
    }
}

void show_query1_driver(Driver d)
{
    if (d != NULL) {
        char *name = driver_get_name(d);
        printf("%s;%c;%d;%.3f;%hu;%.3f\n", name, driver_get_gender(d),
               driver_get_age(d), driver_get_avg_score(d),
               driver_get_n_trips(d), driver_get_total_earned(d));
        free(name);
    }
}

void show_query2(Query2 q2)
{
    for (guint i = 0; i < q2->len; i++) {
        Driver d = (Driver)g_ptr_array_index(q2, i);
        char *name = driver_get_name(d);
        printf("%012ld;%s;%.3f\n", driver_get_id(d), name,
               driver_get_avg_score(d));
        free(name);
    }
}

void show_query3(Query3 q3)
{
    for (guint i = 0; i < q3->len; i++) {
        User u = (User)g_ptr_array_index(q3, i);
        char *name = user_get_name(u);
        char *username = user_get_username(u);
        printf("%s;%s;%d\n", username, name, user_get_total_distance(u));
        free(username);
        free(name);
    }
}

void show_query4(double avg_score)
{
    printf("%.3f\n", avg_score);
}

void show_query5(double avg_cost)
{
    printf("%.3f\n", avg_cost);
}

void show_query6(double avg_distance)
{
    printf("%.3f\n", avg_distance);
}

void show_query7(Query2 drivers, char *city)
{
    for (guint i = 0; i < drivers->len; i++) {
        Driver d = (Driver)g_ptr_array_index(drivers, i);
        char *name = driver_get_name(d);
        printf("%012ld;%s;%.3f\n", driver_get_id(d), name,
               driver_get_city_score(d, city));
        free(name);
    }
}

void show_query9(Query9 q9)
{
    for (guint i = 0; i < q9->len; i++) {
        Ride r = (Ride)g_ptr_array_index(q9, i);
        char *date = days_to_date(ride_get_date(r));
        char *city = ride_get_city(r);
        printf("%012ld;%s;%d;%s;%.3f\n", ride_get_id(r), date,
               (int)ride_get_distance(r), city, ride_get_tip(r));
        free(date);
        free(city);
    }
}
