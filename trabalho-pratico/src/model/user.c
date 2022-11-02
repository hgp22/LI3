#include "user.h"
#include "ride.h"
#include "utils.h"
#include <glib.h>
#include <stdint.h>
#include <string.h>

struct user {
    char *username;
    char *name;
    char gender;
    uint8_t age;
    unsigned short account_age;
    U_Status account_status;
    unsigned short sum_score;
    double total_spent;
    unsigned short total_distance;
    unsigned short n_trips;
    unsigned short last_ride_date;
};

User new_user(void)
{
    User u = g_new(struct user, 1);

    u->sum_score = 0;
    u->total_spent = 0;
    u->total_distance = 0;
    u->n_trips = 0;
    u->last_ride_date = 0;

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
    u->username = strdup(username);
}

void set_user_name(User u, char *name)
{
    u->name = strdup(name);
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

char *get_user_username(User u)
{
    return strdup(u->username);
}

char *get_user_name(User u)
{
    return strdup(u->name);
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

double get_user_avg_score(User u)
{
    double avg_score = 0;
    if (u->n_trips != 0) {
        avg_score = (double)u->sum_score / u->n_trips;
    }
    return avg_score;
}

double get_user_total_spent(User u)
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

unsigned short get_user_last_ride_date(User u)
{
    return u->last_ride_date;
}

void add_user_ride_data(User u, Ride r)
{
    u->sum_score += get_ride_score_user(r);
    u->total_spent += get_ride_cost(r) + get_ride_tip(r);
    u->total_distance += get_ride_distance(r);
    unsigned short ride_date = get_ride_date(r);
    if (ride_date > u->last_ride_date) {
        u->last_ride_date = ride_date;
    }
    u->n_trips += 1;
}

User copy_user(User old_u)
{
    if (old_u == NULL) {
        return NULL;
    }

    User new_u = g_new(struct user, 1);

    new_u->username = strdup(old_u->username);
    new_u->name = strdup(old_u->name);
    new_u->gender = old_u->gender;
    new_u->age = old_u->age;
    new_u->account_age = old_u->account_age;
    new_u->account_status = old_u->account_status;
    new_u->sum_score = old_u->sum_score;
    new_u->total_spent = old_u->total_spent;
    new_u->total_distance = old_u->total_distance;
    new_u->n_trips = old_u->n_trips;
    new_u->last_ride_date = old_u->last_ride_date;

    return new_u;
}
