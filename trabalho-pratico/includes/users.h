#ifndef __USERS_H__
#define __USERS_H__

#include "user.h"
#include <glib.h>

typedef GSList Users;

// #define insert_user(a, b) g_list_prepend(a, b)

/**
 * @brief 
 * 
 * @param users 
 * @param user 
 * @return Users* 
 */
Users *insert_user(Users *users, User *user);

#endif
