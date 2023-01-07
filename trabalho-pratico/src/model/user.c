#include "user.h"
#include "date.h"
#include "validation.h"
#include <ctype.h>
#include <glib.h>
#include <string.h>

typedef enum field_user {
    Username,
    Name,
    Gender,
    Birth_date,
    Account_creation,
    Pay_method,
    Account_status,
} FieldUser;

struct __attribute__((__packed__)) user {
    char *username;
    char *name;
    double total_spent;
    guint16 account_age;
    guint16 sum_score;
    guint16 total_distance;
    guint16 n_trips;
    guint16 last_ride_date;
    char gender;
    guint8 age;
};

User user_new(void)
{
    User u = g_new(struct user, 1);

    u->username = NULL;
    u->name = NULL;
    u->sum_score = 0;
    u->total_spent = 0;
    u->total_distance = 0;
    u->n_trips = 0;
    u->last_ride_date = 0;

    return u;
}

int globalN = 0;

User user_new_from_record(const char *user_record)
{
    User user = user_new();

    for (FieldUser field = Username; field <= Account_status; field++) {
        char *buff = strsep(&user_record, ";\n");
        switch (field) {
            case Username:
                if (*buff == '\0') {
                    user_free(user);
                    return NULL;
                }
                user_set_username(user, buff);
                break;
            case Name:
                if (*buff == '\0') {
                    user_free(user);
                    return NULL;
                }
                user_set_name(user, buff);
                break;
            case Gender:
                if (*buff == '\0') {
                    user_free(user);
                    return NULL;
                }
                user_set_gender(user, buff);
                break;
            case Birth_date:
                if (!validate_date(buff)) {
                    user_free(user);
                    return NULL;
                }
                user_set_age(user, buff);
                break;
            case Account_creation:
                if (!validate_date(buff)) {
                    user_free(user);
                    return NULL;
                }
                user_set_account_age(user, buff);
                break;
            case Pay_method:
                if (*buff == '\0') {
                    user_free(user);
                    return NULL;
                }
                break;
            case Account_status:
                if (!validate_account_status(buff) || tolower(buff[0]) == 'i') {
                    user_free(user);
                    return NULL;
                }
                break;
            default:
                break;
        }
    }

    return user;
}

void user_set_username(const User u, const char *username)
{
    u->username = strdup(username);
}

void user_set_name(const User u, const char *name)
{
    u->name = strdup(name);
}

void user_set_gender(const User u, const char *gender)
{
    u->gender = *gender;
}

void user_set_age(const User u, const char *birth_date)
{
    u->age = date_to_age(birth_date);
}

void user_set_account_age(const User u, const char *account_creation)
{
    u->account_age = date_to_days(account_creation);
}

char *user_get_username(const User u)
{
    return strdup(u->username);
}

char *user_get_name(const User u)
{
    return strdup(u->name);
}

char user_get_gender(const User u)
{
    return u->gender;
}

guint8 user_get_age(const User u)
{
    return u->age;
}

guint16 user_get_account_age(const User u)
{
    return u->account_age;
}

double user_get_avg_score(const User u)
{
    double avg_score = 0;
    if (u->n_trips != 0) {
        avg_score = (double)u->sum_score / u->n_trips;
    }
    return avg_score;
}

double user_get_total_spent(const User u)
{
    return u->total_spent;
}

guint16 user_get_total_distance(const User u)
{
    return u->total_distance;
}

guint16 user_get_n_trips(const User u)
{
    return u->n_trips;
}

guint16 user_get_last_ride_date(const User u)
{
    return u->last_ride_date;
}

void user_add_ride_data(const User u, guint8 score, double cost, guint16 date,
                        guint8 distance)
{
    u->sum_score += score;
    u->total_spent += cost;
    u->total_distance += (guint16)distance;
    u->last_ride_date = date;
    u->n_trips += 1;
}

User user_copy(const User old_u)
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
    new_u->sum_score = old_u->sum_score;
    new_u->total_spent = old_u->total_spent;
    new_u->total_distance = old_u->total_distance;
    new_u->n_trips = old_u->n_trips;
    new_u->last_ride_date = old_u->last_ride_date;

    return new_u;
}

void user_free(void *user)
{
    if (user != NULL) {
        User u = (User)user;
        if (u->username != NULL)
            free(u->username);
        if (u->name != NULL)
            free(u->name);
        free(user);
    }
}
