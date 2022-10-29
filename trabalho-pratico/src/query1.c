#include "query1.h"
#include "driver.h"
#include "user.h"
#include <glib.h>
#include <stdint.h>
#include <stdio.h>

#define GENDER 1
#define AGE 3
#define SCORE 5
#define TRIPS 6
#define COST 9
#define SEMICOLONS 5

char *user_to_q1_string(User u)
{
    char *s = malloc((strlen(get_user_name(u)) + GENDER + AGE + SCORE + TRIPS +
                      COST + SEMICOLONS + 1) *
                     sizeof(char *));

    sprintf(s, "%s;%c;%d;%.3f;%hu;%.3f", get_user_name(u), get_user_gender(u),
            get_user_age(u), get_user_avg_score(u), get_user_n_trips(u),
            get_user_total_spent(u));

    return s;
}

char *driver_to_q1_string(Driver d)
{
    char *s = malloc((strlen(get_driver_name(d)) + GENDER + AGE + SCORE +
                      TRIPS + COST + SEMICOLONS + 1) *
                     sizeof(char *));

    sprintf(s, "%s;%c;%d;%.3f;%hu;%.3f", get_driver_name(d),
            get_driver_gender(d), get_driver_age(d), get_driver_avg_score(d),
            get_driver_n_trips(d), get_driver_total_earned(d));

    return s;
}
