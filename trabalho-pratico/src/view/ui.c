#include "ui.h"
#include "driver.h"
#include "user.h"
#include <stdio.h>

#define GENDER 1
#define AGE 3
#define SCORE 5
#define TRIPS 6
#define MONEY 16
#define SEMICOLONS 5

static int counter = 1;

void show_query1_user(User u)
{
    char file[64];
    sprintf(file, "./Resultados/command%d_output.txt", counter++);
    FILE *command_out = fopen(file, "w");

    if (u != NULL) {
        char *name = get_user_name(u);

        char *answer = malloc((strlen(name) + GENDER + AGE + SCORE + TRIPS +
                               MONEY + SEMICOLONS + 1) *
                              sizeof(char *));

        sprintf(answer, "%s;%c;%d;%.3f;%hu;%.3f", name, get_user_gender(u),
                get_user_age(u), get_user_avg_score(u), get_user_n_trips(u),
                get_user_total_spent(u));

        free(name);

        fprintf(command_out, "%s\n", answer);
    }

    fclose(command_out);
}

void show_query1_driver(Driver d)
{
    char file[64];
    sprintf(file, "./Resultados/command%d_output.txt", counter++);
    FILE *command_out = fopen(file, "w");

    if (d != NULL) {
        char *name = get_driver_name(d);

        char *answer = malloc((strlen(name) + GENDER + AGE + SCORE + TRIPS +
                               MONEY + SEMICOLONS + 1) *
                              sizeof(char *));

        sprintf(answer, "%s;%c;%d;%.3f;%hu;%.3f", name, get_driver_gender(d),
                get_driver_age(d), get_driver_avg_score(d),
                get_driver_n_trips(d), get_driver_total_earned(d));

        free(name);

        fprintf(command_out, "%s\n", answer);
    }

    fclose(command_out);
}

void show_query2(Query2 q2)
{
    char s[64];
    sprintf(s, "./Resultados/command%d_output.txt", counter++);
    FILE *command_out = fopen(s, "w");

    char answer[256];

    for (Query2 itr = q2; itr; itr = itr->next) {
        Driver d = (Driver)itr->data;
        char *name = get_driver_name(d);
        sprintf(answer, "%012ld;%s;%.3f", get_driver_id(d), name,
                get_driver_avg_score(d));
        free(name);
        fprintf(command_out, "%s\n", answer);
    }

    fclose(command_out);
}

void show_query3(Query3 q3)
{
    char s[64];
    sprintf(s, "./Resultados/command%d_output.txt", counter++);
    FILE *command_out = fopen(s, "w");

    char answer[256];

    for (Query3 itr = q3; itr; itr = itr->next) {
        User u = (User)itr->data;
        char *name = get_user_name(u);
        char *username = get_user_username(u);
        sprintf(answer, "%s;%s;%d", username, name, get_user_total_distance(u));
        free(username);
        free(name);
        fprintf(command_out, "%s\n", answer);
    }

    fclose(command_out);
}
