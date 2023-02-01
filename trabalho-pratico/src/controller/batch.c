#include "controller/batch.h"
#include "driver.h"
#include "taxi_system.h"
#include "user.h"
#include "view/batch.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER 64

static int _run_queries(const TaxiSystem ts, const char *queries_path);
static void _query1(const TaxiSystem ts, const char *query, FILE *fp);
static void _query2(const TaxiSystem ts, const char *query, FILE *fp);
static void _query3(const TaxiSystem ts, const char *query, FILE *fp);
static void _query4(const TaxiSystem ts, const char *query, FILE *fp);
static void _query5(const TaxiSystem ts, const char *query, FILE *fp);
static void _query6(const TaxiSystem ts, const char *query, FILE *fp);
static void _query7(const TaxiSystem ts, const char *query, FILE *fp);
static void _query8(const TaxiSystem ts, const char *query, FILE *fp);
static void _query9(const TaxiSystem ts, const char *query, FILE *fp);

int run_batch(const char *inputs_path, const char *queries_path)
{
    TaxiSystem ts = taxi_new(inputs_path);

    if (ts == NULL) {
        printf("Invalid inputs path: %s\n", inputs_path);
        exit(1);
    }

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

    FILE *fp_queries = fopen(queries_path, "r");

    while (getline(&query, &len, fp_queries) != -1) {
        sprintf(file, "./Resultados/command%d_output.txt", n_query++);
        FILE *fp_output = fopen(file, "w");
        run_query(ts, query, fp_output);
        fclose(fp_output);
    }

    free(query);

    return n_query;
}

int run_query(const TaxiSystem ts, const char *query, FILE *fp)
{
    switch (query[0]) {
        case '1':
            _query1(ts, query, fp);
            break;
        case '2':
            _query2(ts, query, fp);
            break;
        case '3':
            _query3(ts, query, fp);
            break;
        case '4':
            _query4(ts, query, fp);
            break;
        case '5':
            _query5(ts, query, fp);
            break;
        case '6':
            _query6(ts, query, fp);
            break;
        case '7':
            _query7(ts, query, fp);
            break;
        case '8':
            _query8(ts, query, fp);
            break;
        case '9':
            _query9(ts, query, fp);
            break;
    }

    return 0;
}

static void _query1(const TaxiSystem ts, const char *query, FILE *fp)
{
    char id[BUFFER];
    sscanf(query, "%*d %s\n", id);
    char *endptr;
    int driver_id = strtol(id, &endptr, 10);
    if (*endptr != '\0') {
        User user = taxi_get_user(ts, id);
        if (user != NULL) {
            batch_print_query1_user(user, fp);
        }
        user_free(user);
    }
    else {
        Driver driver = taxi_get_driver(ts, driver_id);
        if (driver != NULL) {
            batch_print_query1_driver(driver, fp);
        }
        driver_free(driver);
    }
}

static void _query2(const TaxiSystem ts, const char *query, FILE *fp)
{
    int N;
    sscanf(query, "%*d %d", &N);
    GPtrArray *drivers = taxi_top_n_drivers_by_score(ts, N);
    batch_print_query2(drivers, fp);
    g_ptr_array_free(drivers, TRUE);
}

static void _query3(const TaxiSystem ts, const char *query, FILE *fp)
{
    int N;
    sscanf(query, "%*d %d", &N);
    GPtrArray *users = taxi_top_n_users_by_distance(ts, N);
    batch_print_query3(users, fp);
    g_ptr_array_free(users, TRUE);
}

static void _query4(const TaxiSystem ts, const char *query, FILE *fp)
{
    char city[BUFFER];
    sscanf(query, "%*d %s", city);
    double avg_cost = taxi_city_avg_cost(ts, city);
    if (avg_cost > 0) {
        batch_print_query4(avg_cost, fp);
    }
}

static void _query5(const TaxiSystem ts, const char *query, FILE *fp)
{
    char dateA[BUFFER], dateB[BUFFER];
    sscanf(query, "%*d %s %s", dateA, dateB);
    double avg_cost = taxi_avg_cost_in_range(ts, dateA, dateB);
    if (avg_cost == avg_cost) { // check if avg_cost is NaN
        batch_print_query5(avg_cost, fp);
    }
}

static void _query6(const TaxiSystem ts, const char *query, FILE *fp)
{
    char city[BUFFER], dateA[BUFFER], dateB[BUFFER];
    sscanf(query, "%*d %s %s %s", city, dateA, dateB);
    double avg_dist = taxi_city_avg_dist_in_range(ts, city, dateA, dateB);
    if (avg_dist > 0) {
        batch_print_query6(avg_dist, fp);
    }
}

static void _query7(const TaxiSystem ts, const char *query, FILE *fp)
{
    int N;
    char city[BUFFER];
    sscanf(query, "%*d %d %s", &N, city);
    GPtrArray *drivers = taxi_top_n_drivers_in_city(ts, city, N);
    if (drivers != NULL) {
        batch_print_query7(drivers, city, fp);
        g_ptr_array_free(drivers, TRUE);
    }
}

static void _query8(const TaxiSystem ts, const char *query, FILE *fp)
{
    char gender;
    int account_age;
    sscanf(query, "%*d %c %d", &gender, &account_age);
    GPtrArray *rides = taxi_rides_by_gender_by_age(ts, gender, account_age);
    batch_print_query8(rides, ts, fp);
    g_ptr_array_free(rides, TRUE);
}

static void _query9(const TaxiSystem ts, const char *query, FILE *fp)
{
    char dateA2[BUFFER];
    char dateB2[BUFFER];
    sscanf(query, "%*d %s %s", dateA2, dateB2);
    GPtrArray *rides = taxi_rides_with_tip_in_range(ts, dateA2, dateB2);
    batch_print_query9(rides, fp);
    g_ptr_array_free(rides, TRUE);
}
