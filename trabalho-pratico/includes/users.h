#ifndef __USERS_H__
#define __USERS_H__

#include "user.h"
#include <glib.h>

typedef GSList *Users;

/**
 * @brief
 *
 * @param users
 * @param user
 * @return Users
 */
Users insert_user(Users users, User user);

#endif
