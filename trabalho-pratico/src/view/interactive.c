#include "view/interactive.h"
#include "date.h"
#include "driver.h"
#include "output.h"
#include "ride.h"
#include "taxi_system.h"
#include "user.h"
#include <curses.h>
#include <stdio.h>

#define BUFFER 128

static void _free_lines(gpointer data);

Output interactive_query1_user(const User u)
{
    if (u == NULL) {
        return NULL;
    }

    GPtrArray *lines = g_ptr_array_new_full(6, free);

    char *line = malloc(BUFFER * sizeof(*line));
    sprintf(line, "Name:            %s\n", user_get_name(u));
    g_ptr_array_add(lines, line);
    line = malloc(BUFFER * sizeof(*line));
    sprintf(line, "Gender:          %c\n", user_get_gender(u));
    g_ptr_array_add(lines, line);
    line = malloc(BUFFER * sizeof(*line));
    sprintf(line, "Age:             %d\n", user_get_age(u));
    g_ptr_array_add(lines, line);
    line = malloc(BUFFER * sizeof(*line));
    sprintf(line, "Average score:   %.3f\n", user_get_avg_score(u));
    g_ptr_array_add(lines, line);
    line = malloc(BUFFER * sizeof(*line));
    sprintf(line, "Number of trips: %hu\n", user_get_n_trips(u));
    g_ptr_array_add(lines, line);
    line = malloc(BUFFER * sizeof(*line));
    sprintf(line, "Total spent:     %.3f\n", user_get_total_spent(u));
    g_ptr_array_add(lines, line);

    Output output = output_build_lines(lines);

    g_ptr_array_free(lines, TRUE);

    return output;
}

Output interactive_query1_driver(const Driver d)
{
    if (d == NULL) {
        return NULL;
    }

    GPtrArray *lines = g_ptr_array_new_full(6, free);

    char *line = malloc(BUFFER * sizeof(*line));
    sprintf(line, "Name:            %s\n", driver_get_name(d));
    g_ptr_array_add(lines, line);
    line = malloc(BUFFER * sizeof(*line));
    sprintf(line, "Gender:          %c\n", driver_get_gender(d));
    g_ptr_array_add(lines, line);
    line = malloc(BUFFER * sizeof(*line));
    sprintf(line, "Age:             %d\n", driver_get_age(d));
    g_ptr_array_add(lines, line);
    line = malloc(BUFFER * sizeof(*line));
    sprintf(line, "Average score:   %.3f\n", driver_get_avg_score(d));
    g_ptr_array_add(lines, line);
    line = malloc(BUFFER * sizeof(*line));
    sprintf(line, "Number of trips: %hu\n", driver_get_n_trips(d));
    g_ptr_array_add(lines, line);
    line = malloc(BUFFER * sizeof(*line));
    sprintf(line, "Total earned:    %.3f\n", driver_get_total_earned(d));
    g_ptr_array_add(lines, line);

    Output output = output_build_lines(lines);

    g_ptr_array_free(lines, TRUE);

    return output;
}

Output interactive_query2(const GPtrArray *drivers)
{
    if (drivers->len == 0) {
        return NULL;
    }

    GPtrArray *lines =
        g_ptr_array_new_full(drivers->len, (GDestroyNotify)_free_lines);

    for (guint i = 0; i < drivers->len; i++) {
        Driver d = g_ptr_array_index(drivers, i);
        GPtrArray *fields = g_ptr_array_new_full(3, (GDestroyNotify)g_free);
        g_ptr_array_add(fields, driver_show_id(d));
        g_ptr_array_add(fields, driver_show_name(d));
        g_ptr_array_add(fields, driver_show_avg_score(d));
        g_ptr_array_add(lines, fields);
    }

    char *headers[3] = {"id", "name", "average score"};
    int sizes[] = {12, 0, 5};

    Output output = output_build_table(lines, sizes, headers);

    g_ptr_array_free(lines, TRUE);

    return output;
}

Output interactive_query3(const GPtrArray *users)
{
    if (users->len == 0) {
        return NULL;
    }

    GPtrArray *lines =
        g_ptr_array_new_full(users->len, (GDestroyNotify)_free_lines);

    for (guint i = 0; i < users->len; i++) {
        User u = g_ptr_array_index(users, i);
        GPtrArray *fields = g_ptr_array_new_full(3, (GDestroyNotify)g_free);
        g_ptr_array_add(fields, user_show_username(u));
        g_ptr_array_add(fields, user_show_name(u));
        g_ptr_array_add(fields, user_show_total_distance(u));
        g_ptr_array_add(lines, fields);
    }

    char *headers[3] = {"username", "name", "total distance"};
    int sizes[] = {0, 0, 0};

    Output output = output_build_table(lines, sizes, headers);

    g_ptr_array_free(lines, TRUE);

    return output;
}

Output interactive_query4(double avg_score)
{
    GPtrArray *lines = g_ptr_array_new_full(1, free);

    char *line = malloc(BUFFER * sizeof(*line));
    sprintf(line, "Average score: %.3f\n", avg_score);
    g_ptr_array_add(lines, line);

    Output output = output_build_lines(lines);

    g_ptr_array_free(lines, TRUE);

    return output;
}

Output interactive_query5(double avg_cost)
{
    GPtrArray *lines = g_ptr_array_new_full(1, free);

    char *line = malloc(BUFFER * sizeof(*line));
    sprintf(line, "Average cost: %.3f\n", avg_cost);
    g_ptr_array_add(lines, line);

    Output output = output_build_lines(lines);

    g_ptr_array_free(lines, TRUE);

    return output;
}

Output interactive_query6(double avg_distance)
{
    GPtrArray *lines = g_ptr_array_new_full(1, free);

    char *line = malloc(BUFFER * sizeof(*line));
    sprintf(line, "Average distance: %.3f\n", avg_distance);
    g_ptr_array_add(lines, line);

    Output output = output_build_lines(lines);

    g_ptr_array_free(lines, TRUE);

    return output;
}

Output interactive_query7(const GPtrArray *drivers, const char *city)
{
    if (drivers->len == 0) {
        return NULL;
    }

    GPtrArray *lines =
        g_ptr_array_new_full(drivers->len, (GDestroyNotify)_free_lines);

    for (guint i = 0; i < drivers->len; i++) {
        Driver d = g_ptr_array_index(drivers, i);
        GPtrArray *fields = g_ptr_array_new_full(3, (GDestroyNotify)g_free);
        g_ptr_array_add(fields, driver_show_id(d));
        g_ptr_array_add(fields, driver_show_name(d));
        g_ptr_array_add(fields, driver_show_city_score(d, city));
        g_ptr_array_add(lines, fields);
    }

    char *headers[3] = {"id", "name", "city score"};
    int sizes[] = {12, 0, 5};

    Output output = output_build_table(lines, sizes, headers);

    g_ptr_array_free(lines, TRUE);

    return output;
}

Output interactive_query8(const GPtrArray *rides, const TaxiSystem ts)
{
    if (rides->len == 0) {
        return NULL;
    }

    GPtrArray *lines =
        g_ptr_array_new_full(rides->len, (GDestroyNotify)_free_lines);

    for (guint i = 0; i < rides->len; i++) {
        Ride r = g_ptr_array_index(rides, i);
        int driver = ride_get_driver(r);
        char *user = ride_get_user(r);
        Driver d = taxi_get_driver(ts, driver);
        User u = taxi_get_user(ts, user);
        free(user);
        GPtrArray *fields = g_ptr_array_new_full(5, (GDestroyNotify)g_free);
        g_ptr_array_add(fields, driver_show_id(d));
        g_ptr_array_add(fields, driver_show_name(d));
        driver_free(d);
        g_ptr_array_add(fields, user_show_username(u));
        g_ptr_array_add(fields, user_show_name(u));
        user_free(u);
        g_ptr_array_add(lines, fields);
    }

    char *headers[] = {"driver id", "driver name", "username", "user name"};
    int sizes[] = {12, 0, 0, 0};

    Output output = output_build_table(lines, sizes, headers);

    g_ptr_array_free(lines, TRUE);

    return output;
}

Output interactive_query9(const GPtrArray *rides)
{
    if (rides == NULL) {
        return NULL;
    }

    if (rides->len == 0) {
        return NULL;
    }

    GPtrArray *lines =
        g_ptr_array_new_full(rides->len, (GDestroyNotify)_free_lines);

    for (guint i = 0; i < rides->len; i++) {
        Ride r = g_ptr_array_index(rides, i);
        GPtrArray *fields = g_ptr_array_new_full(5, (GDestroyNotify)g_free);
        g_ptr_array_add(fields, ride_show_id(r));
        g_ptr_array_add(fields, ride_show_date(r));
        g_ptr_array_add(fields, ride_show_distance(r));
        g_ptr_array_add(fields, ride_show_city(r));
        g_ptr_array_add(fields, ride_show_tip(r));
        g_ptr_array_add(lines, fields);
    }

    char *headers[] = {"id", "date", "distance", "city", "tip"};
    int sizes[] = {12, 10, 0, 0, 0};

    Output output = output_build_table(lines, sizes, headers);

    g_ptr_array_free(lines, TRUE);

    return output;
}

Output interactive_help(void)
{
    guint help_lines = 25;
    char *help[] = {
        "MAIN COMMANDS\n",
        ":h                       Display this help.\n",
        ":l <path>                Load dataset in <path>.\n",
        ":q                       Exit.\n",
        "\n",
        "QUERY COMMANDS\n",
        "1 <ID>                   Summary of <ID< profile.\n",
        "2 <N>                    Top <N> drivers.\n",
        "3 <N>                    Top <N> users.\n",
        "4 <city>                 Avg trip cost in <city>.\n",
        "5 <dateA> <dateB>        Avg trip cost from <dateA> to <dateB>.\n",
        "6 <city> <dateA> <dateB> Avg trip dist in <city> from <dateA> to "
        "<dateB>.\n",
        "7 <N> <city>             Top <N> drivers in <city>.\n",
        "8 <gender> <X>           Trips with <gender> drivers and users w/ "
        "profile older than <X>.\n",
        "9 <dateA> <dateB>        TRips with tip from <dateA> to <dateB>.\n",
        "\n",
        "MOVING\n",
        "j DownArrow DownScroll   Forward  one line.\n",
        "k DownArrow DownScroll   Backward one line.\n",
        "J                        Forward  one page.\n",
        "K                        Backward one page.\n",
        "\n",
        "JUMPING\n",
        "g                        Go to first line.\n",
        "G                        Go to last  line.\n"};

    GPtrArray *lines = g_ptr_array_new_full(help_lines, free);

    for (guint i = 0; i < help_lines; i++) {
        g_ptr_array_add(lines, strdup(help[i]));
    }

    Output output = output_build_lines(lines);

    g_ptr_array_free(lines, TRUE);

    return output;
}

static void _free_lines(gpointer data)
{
    g_ptr_array_free(data, TRUE);
}
