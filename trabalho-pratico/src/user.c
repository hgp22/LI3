#include "user.h"
#include "ride.h"
#include "utils.h"
#include <glib.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct user {
    char *username;
    char *name;
    char gender;
    uint8_t age;
    unsigned short account_age;
    U_Status account_status;
    unsigned short sum_score;
    float total_spent;
    unsigned short total_distance;
    unsigned short n_trips;
    GSList *recent_trips;
};

User new_user(void)
{
    User u = g_new(struct user, 1);

    u->sum_score = 0;
    u->total_spent = 0;
    u->total_distance = 0;
    u->n_trips = 0;
    u->recent_trips = NULL;

    return u;
}

void free_user(void *user)
{
    User u = (User)user;
    free(u->username);
    free(u->name);
    g_slist_free(g_steal_pointer(&u->recent_trips));
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
    u->age = date_to_age(birth_date);
}

void set_user_account_age(User u, char *account_creation)
{
    u->account_age = date_to_days(account_creation);
}

void set_user_account_status(User u, char *account_status)
{
    switch (account_status[0]) {
        case 'i':
            u->account_status = U_Inactive;
            break;
        case 'a':
            u->account_status = U_Active;
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

U_Status get_user_account_status(User u)
{
    return u->account_status;
}

float get_user_avg_score(User u)
{
    float avg_score = 0;
    if (u->n_trips != 0) {
        avg_score = (float)u->sum_score / u->n_trips;
    }
    return avg_score;
}

float get_user_total_spent(User u)
{
    return u->total_spent;
}

unsigned short get_user_total_distance(User u)
{
    return u->total_distance;
}

unsigned short get_user_n_trips(User u)
{
    return u->n_trips;
}

GSList *get_user_trip_dates(User u)
{
    return u->recent_trips;
}

void add_user_ride_data(User u, Ride r)
{
    u->sum_score += get_ride_score_user(r);
    u->total_spent += get_ride_cost(r) + get_ride_tip(r);
    u->total_distance += get_ride_distance(r);
    u->recent_trips = g_slist_insert_sorted(u->recent_trips,
                                            GINT_TO_POINTER(get_ride_date(r)),
                                            (GCompareFunc)compare_trips);
    u->n_trips += 1;
}
