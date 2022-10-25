#include "query1.h"
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

struct query1 {
    char *name;
    char gender;
    uint8_t age;
    int sum_score;
    unsigned short number_trips;
    int total_spent;
};

Query1 init_query1(User u)
{
    Query1 q = g_new(struct query1, 1);

    q->name = get_user_name(u);
    q->gender = get_user_gender(u);
    q->age = get_user_age(u);
    q->sum_score = 0;
    q->number_trips = 0;
    q->total_spent = 0;

    return q;
}

void add_score(Query1 q, unsigned short score)
{
    q->sum_score += score;
    q->number_trips++;
}

void add_trip(Query1 q)
{
    q->number_trips++;
}

void add_money(Query1 q, int money)
{
    q->total_spent += money;
}

char *query1_to_string(Query1 q)
{
    char *s = (char *)malloc((strlen(q->name) + GENDER + AGE + SCORE + TRIPS +
                              COST + SEMICOLONS + 1) *
                             sizeof(char *));

    float avg_score = q->sum_score / q->number_trips;

    sprintf(s, "%s;%c;%d;%ff%d;%d", q->name, q->gender, q->age, avg_score,
            q->number_trips, q->total_spent);

    return s;
}
