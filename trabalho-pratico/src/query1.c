#include "query1.h"
#include "catalog.h"
#include "driver.h"
#include "user.h"
#include "utils.h"
#include <glib.h>
#include <stdint.h>
#include <stdio.h>

#define GENDER 1
#define AGE 3
#define SCORE 5
#define TRIPS 6
#define MONEY 16
#define SEMICOLONS 5

// ! remove IO from function
void query1(Catalog c, char *id)
{
    char *endptr;
    long driver = strtol(id, &endptr, 10);

    if (*endptr != '\0') {
        User u = g_hash_table_lookup(get_catalog_users(c), id);
        if (u != NULL && get_user_account_status(u)) {
            char *q1_answer = _user_to_q1_string(u);
            printf("%s\n", q1_answer);
            free(q1_answer);
        }
    }
    else {
        Driver d = g_hash_table_lookup(get_catalog_drivers(c), &driver);
        if (d != NULL && get_driver_account_status(d)) {
            char *q1_answer = _driver_to_q1_string(d);
            printf("%s\n", q1_answer);
            free(q1_answer);
        }
    }
}

static char *_user_to_q1_string(User u)
{
    char *name = get_user_name(u);

    char *s = malloc(
        (strlen(name) + GENDER + AGE + SCORE + TRIPS + MONEY + SEMICOLONS + 1) *
        sizeof(char *));

    sprintf(s, "%s;%c;%d;%.3f;%hu;%.3f", name, get_user_gender(u),
            get_user_age(u), get_user_avg_score(u), get_user_n_trips(u),
            get_user_total_spent(u));

    free(name);

    return s;
}

static char *_driver_to_q1_string(Driver d)
{
    char *name = get_driver_name(d);

    char *s = malloc(
        (strlen(name) + GENDER + AGE + SCORE + TRIPS + MONEY + SEMICOLONS + 1) *
        sizeof(char *));

    sprintf(s, "%s;%c;%d;%.3f;%hu;%.3f", name, get_driver_gender(d),
            get_driver_age(d), get_driver_avg_score(d), get_driver_n_trips(d),
            get_driver_total_earned(d));

    free(name);

    return s;
}
