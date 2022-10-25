#include "user.h"
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
    short account_creation;
    char *pay_method;
    Status account_status;
};

User init_user(void)
{
    return g_new(struct user, 1);
}

void free_user(void *user)
{
    User u = (User)user;
    free(u->username);
    free(u->name);
    free(u->pay_method);
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

void set_user_account_creation(User u, char *account_creation)
{
    short d, m, y;
    sscanf(account_creation, "%hd/%hd/%hd", &d, &m, &y);

    int months[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    int leaps = (y - 1970 + 2) / 4; // works until 2100
    int days = (y - 1970) * 365 + months[m - 1] + d + leaps;

    u->account_creation = days;
}

void set_user_pay_method(User u, char *pay_method)
{
    u->pay_method = malloc(strlen(pay_method) * sizeof(pay_method));
    strcpy(u->pay_method, pay_method);
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

short get_user_account_creation(User u)
{
    return u->account_creation;
}

char *get_user_pay_method(User u)
{
    return strdup(u->pay_method);
}

Status get_user_account_status(User u)
{
    return u->account_status;
}
