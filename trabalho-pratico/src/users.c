#include "user.h"
#include "users.h"

Users *insert_user(Users *users, User *user)
{
    return g_slist_prepend(users, user);
}
