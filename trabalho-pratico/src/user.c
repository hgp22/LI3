#include "user.h"
#include "ride.h"
#include "utils.h"
#include <glib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct user {
    char *username;
    char *name;
    char gender;
    uint8_t age;
    unsigned short account_age;
    unsigned short sum_score;
    float total_spent;
    unsigned short total_distance;
    unsigned short n_trips;
    GSList *recent_trips;
    Status account_status;
};

User new_user(void)
{
    User u = g_new(struct user, 1);

    u->sum_score = 0;
    u->total_spent = 0;
    u->total_distance = 0;
    u->n_trips = 0;
    // ? do we need to initialize the list?

    return u;
}

void free_user(void *user)
{
    User u = (User)user;
    free(u->username);
    free(u->name);
    free(user);
}

void set_user_username(User u, char *username)
{
    u->username = malloc(strlen(username) * sizeof(username));
    strcpy(u->username, username);
}

void set_user_name(User u, char *name)
{
    u->name = malloc(strlen(name) * sizeof(name));
    strcpy(u->name, name);
}

void set_user_gender(User u, char *gender)
{
    u->gender = *gender;
}

void set_user_age(User u, char *birth_date)
{
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    local->tm_mon++;

    short d, m, y;
    sscanf(birth_date, "%hd/%hd/%hd", &d, &m, &y);

    uint8_t age = local->tm_year - (y - 1900);

    if (local->tm_mon < m || (local->tm_mon == m && local->tm_mday < d)) {
        age--;
    }

    u->age = age;
}

void set_user_account_age(User u, char *account_creation)
{
    u->account_age = date_to_days(account_creation);
}

void set_user_account_status(User u, char *account_status)
{
    switch (account_status[0]) {
        case 'i':
            u->account_status = Inactive;
            break;
        case 'a':
            u->account_status = Active;
            break;
        default:
            break;
    }
}

char *get_user_name(User u)
{
    return strdup(u->name);
}

char *get_user_username(User u)
{
    return strdup(u->username);
}

char get_user_gender(User u)
{
    return u->gender;
}

uint8_t get_user_age(User u)
{
    return u->age;
}

unsigned short get_user_account_age(User u)
{
    return u->account_age;
}

float get_user_avg_score(User u)
{
    return u->sum_score / u->n_trips;
}

float get_user_total_spent(User u)
{
    return u->total_spent;
}

int get_user_total_distance(User u)
{
    return u->total_distance;
}

float get_user_n_trips(User u)
{
    return u->n_trips;
}

GSList *get_user_trip_dates(User u)
{
    return u->recent_trips;
}

Status get_user_account_status(User u)
{
    return u->account_status;
}

void add_user_ride_data(User u, Ride r)
{
    u->sum_score += get_ride_score_user(r);
    u->total_spent += get_ride_cost(r);
    u->total_distance += get_ride_distance(r);
    // ! doubt this works, isn't date lost?
    unsigned short date = get_ride_date(r);
    u->recent_trips =
        g_slist_insert_sorted(u->recent_trips, &date, compare_trips);
    u->n_trips += 1;
}
