#include "query1.h"
#include "catalog.h"
#include "driver.h"
#include "user.h"
#include "utils.h"
#include <stdint.h>
#include <stdio.h>

#define GENDER 1
#define AGE 3
#define SCORE 5
#define TRIPS 6
#define MONEY 16
#define SEMICOLONS 5

extern int counter;

// ! remove IO from function
void query1(Catalog c, char *id)
{
    char *endptr;
    long driver = strtol(id, &endptr, 10);

    char *s = malloc(34 * sizeof(char *));
    sprintf(s, "./Resultados/command%d_output.txt", counter++);
    FILE *command_out = fopen(s, "w");
    free(s);

    if (*endptr != '\0') {
        User u = get_catalog_user(c, id);
        if (u != NULL && get_user_account_status(u)) {
            char *q1_answer = _user_to_q1_string(u);
            fprintf(command_out, "%s\n", q1_answer);
            free(q1_answer);
        }
    }
    else {
        Driver d = get_catalog_driver(c, driver);
        if (d != NULL && get_driver_account_status(d)) {
            char *q1_answer = _driver_to_q1_string(d);
            fprintf(command_out, "%s\n", q1_answer);
            free(q1_answer);
        }
    }

    fclose(command_out);
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
