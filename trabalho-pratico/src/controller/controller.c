#include "controller.h"
#include "driver.h"
#include "rides.h"
#include "taxi_system.h"
#include "ui.h"
#include "user.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER 64

static int _run_queries(const TaxiSystem ts, const char *queries_path);
static int _run_query(const TaxiSystem ts, const char *query);
static void _query1(const TaxiSystem ts, const char *query);
static void _query2(const TaxiSystem ts, const char *query);
static void _query3(const TaxiSystem ts, const char *query);
static void _query4(const TaxiSystem ts, const char *query);
static void _query5(const TaxiSystem ts, const char *query);
static void _query6(const TaxiSystem ts, const char *query);
static void _query7(const TaxiSystem ts, const char *query);
static void _query8(const TaxiSystem ts, const char *query);
static void _query9(const TaxiSystem ts, const char *query);

int run_controller(const char *inputs_path, const char *queries_path)
{
    TaxiSystem ts = taxi_new(inputs_path);

    struct stat st = {0};

    if (stat("Resultados", &st) == -1) {
        mkdir("Resultados", 0700);
    }

    int r = _run_queries(ts, queries_path);

    taxi_free(ts);

    return r;
}

static int _run_queries(const TaxiSystem ts, const char *queries_path)
{
    char *query = NULL;
    size_t len = 0;
    char file[BUFFER];
    int n_query = 1;

    FILE *fp = freopen(queries_path, "r", stdin);

    while (getline(&query, &len, stdin) != -1) {
        sprintf(file, "./Resultados/command%d_output.txt", n_query++);
        fp = freopen(file, "w", stdout);
        _run_query(ts, query);
    }

    fclose(fp);
    free(query);

    return n_query;
}

static int _run_query(const TaxiSystem ts, const char *query)
{
    switch (query[0]) {
        case '1':
            _query1(ts, query);
            break;
        case '2':
            _query2(ts, query);
            break;
        case '3':
            _query3(ts, query);
            break;
        case '4':
            _query4(ts, query);
            break;
        case '5':
            _query5(ts, query);
            break;
        case '6':
            _query6(ts, query);
            break;
        case '7':
            _query7(ts, query);
            break;
        case '8':
            _query8(ts, query);
            break;
        case '9':
            _query9(ts, query);
            break;
    }

    return 0;
}

static void _query1(const TaxiSystem ts, const char *query)
{
    // If User and Driver could be generalized to Person
    // we could simply do show_query1(query1(c, id))
    // where query1 returns and show_query1 receives a Person
    char id[BUFFER];
    sscanf(query, "%*d %s\n", id);
    char *endptr;
    int driver = strtol(id, &endptr, 10);
    if (*endptr != '\0') {
        User u = taxi_get_user(ts, id);
        show_query1_user(u);
        user_free(u);
    }
    else {
        Driver d = taxi_get_driver(ts, driver);
        show_query1_driver(d);
        driver_free(d);
    }
}

static void _query2(const TaxiSystem ts, const char *query)
{
    int N;
    sscanf(query, "%*d %d", &N);
    GPtrArray *drivers = taxi_top_n_drivers_by_score(ts, N);
    show_query2(drivers);
    g_ptr_array_free(drivers, TRUE);
}

static void _query3(const TaxiSystem ts, const char *query)
{
    int N;
    sscanf(query, "%*d %d", &N);
    GPtrArray *users = taxi_top_n_users_by_distance(ts, N);
    show_query3(users);
    g_ptr_array_free(users, TRUE);
}

static void _query4(const TaxiSystem ts, const char *query)
{
    char city[BUFFER];
    sscanf(query, "%*d %s", city);
    double avg_cost = taxi_city_avg_cost(ts, city);
    if (avg_cost > 0) {
        show_query4(avg_cost);
    }
}

static void _query5(const TaxiSystem ts, const char *query)
{
    char dateA[BUFFER], dateB[BUFFER];
    sscanf(query, "%*d %s %s", dateA, dateB);
    double avg_cost = taxi_avg_cost_in_range(ts, dateA, dateB);
    if (avg_cost == avg_cost) { // check if avg_cost is NaN
        show_query5(avg_cost);
    }
}

static void _query6(const TaxiSystem ts, const char *query)
{
    char city[BUFFER], dateA[BUFFER], dateB[BUFFER];
    sscanf(query, "%*d %s %s %s", city, dateA, dateB);
    double avg_dist = taxi_city_avg_dist_in_range(ts, city, dateA, dateB);
    if (avg_dist > 0) {
        show_query6(avg_dist);
    }
}

static void _query7(const TaxiSystem ts, const char *query)
{
    int N;
    char city[BUFFER];
    sscanf(query, "%*d %d %s", &N, city);
    GPtrArray *drivers = taxi_top_n_drivers_in_city(ts, city, N);
    if (drivers != NULL) {
        show_query7(drivers, city);
        g_ptr_array_free(drivers, TRUE);
    }
}

static void _query8(const TaxiSystem ts, const char *query)
{
    char gender;
    int account_age;
    sscanf(query, "%*d %c %d", &gender, &account_age);
    GPtrArray *rides = taxi_query8(ts, gender, account_age);
    show_query8(rides, ts);
    g_ptr_array_free(rides, TRUE);
}

static void _query9(const TaxiSystem ts, const char *query)
{
    char dateA2[BUFFER];
    char dateB2[BUFFER];
    sscanf(query, "%*d %s %s", dateA2, dateB2);
    GPtrArray *rides = taxi_rides_with_tip_in_range(ts, dateA2, dateB2);
    show_query9(rides);
    g_ptr_array_free(rides, TRUE);
}
