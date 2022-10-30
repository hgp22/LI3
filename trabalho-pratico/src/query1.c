#include "query1.h"
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

char *user_to_q1_string(User u)
{
    char *name = get_user_name(u);

    char *s = malloc((strlen(name) + GENDER + AGE + SCORE + TRIPS +
                      MONEY + SEMICOLONS + 1) *
                     sizeof(char *));

    char *avg_score = ftoa_no_trailing_z(get_user_avg_score(u));
    char *total_spent = ftoa_no_trailing_z(get_user_total_spent(u));

    sprintf(s, "%s;%c;%d;%s;%hu;%s", name, get_user_gender(u),
            get_user_age(u), avg_score,
            get_user_n_trips(u), total_spent);

    free(name);
    free(avg_score);
    free(total_spent);

    return s;
}

char *driver_to_q1_string(Driver d)
{
    char *name = get_driver_name(d);

    char *s = malloc((strlen(name) + GENDER + AGE + SCORE +
                      TRIPS + MONEY + SEMICOLONS + 1) *
                     sizeof(char *));

    char *total_earned = ftoa_no_trailing_z(get_driver_total_earned(d));
    char *avg_score = ftoa_no_trailing_z(get_driver_avg_score(d));

    sprintf(s, "%s;%c;%d;%s;%hu;%s", name, get_driver_gender(d),
            get_driver_age(d), avg_score,
            get_driver_n_trips(d), total_earned);

    free(name);
    free(avg_score);
    free(total_earned);

    return s;
}
