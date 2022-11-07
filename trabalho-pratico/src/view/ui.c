#include "ui.h"
#include "driver.h"
#include "user.h"
#include <stdio.h>

static int counter = 1;

FILE *next_output_file(void)
{
    char file[64];
    sprintf(file, "./Resultados/command%d_output.txt", counter++);
    return freopen(file, "w", stdout);

void show_query1_user(User u)
{
    if (u != NULL) {
        char answer[256];
        char *name = get_user_name(u);
        sprintf(answer, "%s;%c;%d;%.3f;%hu;%.3f", name, get_user_gender(u),
                get_user_age(u), get_user_avg_score(u), get_user_n_trips(u),
                get_user_total_spent(u));
        free(name);
        printf("%s\n", answer);
    }
}

void show_query1_driver(Driver d)
{
    if (d != NULL) {
        char answer[256];
        char *name = get_driver_name(d);
        sprintf(answer, "%s;%c;%d;%.3f;%hu;%.3f", name, get_driver_gender(d),
                get_driver_age(d), get_driver_avg_score(d),
                get_driver_n_trips(d), get_driver_total_earned(d));
        free(name);
        printf("%s\n", answer);
    }
}

void show_query2(Query2 q2)
{
    char answer[256];

    for (guint i = 0; i < q2->len; i++) {
        Driver d = (Driver)g_ptr_array_index(q2, i);
        char *name = get_driver_name(d);
        sprintf(answer, "%012ld;%s;%.3f", get_driver_id(d), name,
                get_driver_avg_score(d));
        free(name);
        printf("%s\n", answer);
    }
}

void show_query3(Query3 q3)
{
    char answer[256];

    for (guint i = 0; i < q3->len; i++) {
        User u = (User)g_ptr_array_index(q3, i);
        char *name = get_user_name(u);
        char *username = get_user_username(u);
        sprintf(answer, "%s;%s;%d", username, name, get_user_total_distance(u));
        free(username);
        free(name);
        printf("%s\n", answer);
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
