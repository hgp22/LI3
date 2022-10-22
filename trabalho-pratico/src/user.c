#include "user.h"
#include <glib.h>
#include <stdlib.h>
#include <string.h>

struct user {
    char *username;
    char *name;
    char *gender;
    char *birth_date;
    char *account_creation;
    char *pay_method;
    char *account_status;
};

User init_user(void) { return g_new(struct user, 1); }

void free_user(void *user)
{
    User u = (User)user;
    free(u->username);
    free(u->name);
    free(u->gender);
    free(u->birth_date);
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
    u->gender = malloc(strlen(gender) * sizeof(gender));
    strcpy(u->gender, gender);
}

void set_user_birth_date(User u, char *birth_date)
{
    u->birth_date = malloc(strlen(birth_date) * sizeof(birth_date));
    strcpy(u->birth_date, birth_date);
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

char *get_user_name(User u) { return strdup(u->name); }

char *get_user_username(User u) { return strdup(u->username); }

char *get_user_gender(User u) { return strdup(u->gender); }

char *get_user_birth_date(User u) { return strdup(u->birth_date); }

char *get_user_account_creation(User u) { return strdup(u->account_creation); }

char *get_user_pay_method(User u) { return strdup(u->pay_method); }

char *get_user_account_status(User u) { return strdup(u->account_status); }
