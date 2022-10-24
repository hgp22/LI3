#include "user.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define AGE_LEN 4

struct user {
    char *username;
    char *name;
    Gender gender;
    char *age;
    char *account_creation;
    char *pay_method;
    char *account_status;
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
    free(u->age);
    free(u->account_creation);
    free(u->pay_method);
    free(u->account_status);
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
    switch (*gender) {
        case 'M':
            u->gender = Male;
            break;
        case 'F':
            u->gender = Female;
            break;
        default:
            break;
    }
}

void set_user_age(User u, char *birth_date)
{
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    local->tm_mon++;

    short d, m, y;
    sscanf(birth_date, "%hd/%hd/%hd", &d, &m, &y);

    short age = local->tm_year - (y - 1900);

    if (local->tm_mon < m || (local->tm_mon == m && local->tm_mday < d)) {
        age--;
    }

    u->age = (char *)malloc(AGE_LEN * sizeof(birth_date));

    sprintf(u->age, "%hd", age);
}

void set_user_account_creation(User u, char *account_creation)
{
    u->account_creation =
        malloc(strlen(account_creation) * sizeof(account_creation));
    strcpy(u->account_creation, account_creation);
}

void set_user_pay_method(User u, char *pay_method)
{
    u->pay_method = malloc(strlen(pay_method) * sizeof(pay_method));
    strcpy(u->pay_method, pay_method);
}

void set_user_account_status(User u, char *account_status)
{
    u->account_status = malloc(strlen(account_status) * sizeof(account_status));
    strcpy(u->account_status, account_status);
}

char *get_user_name(User u)
{
    return strdup(u->name);
}

char *get_user_username(User u)
{
    return strdup(u->username);
}

Gender get_user_gender(User u)
{
    return u->gender;
}

char *get_user_age(User u)
{
    return strdup(u->age);
}

char *get_user_account_creation(User u)
{
    return strdup(u->account_creation);
}

char *get_user_pay_method(User u)
{
    return strdup(u->pay_method);
}

char *get_user_account_status(User u)
{
    return strdup(u->account_status);
}
