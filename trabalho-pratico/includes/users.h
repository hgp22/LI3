#ifndef __USERS_H__
#define __USERS_H__

#include "user.h"
#include <glib.h>

typedef GHashTable *Users;

/**
 * @brief
 *
 * @return Users
 */
Users new_users(void);

/**
 * @brief
 *
 * @param users
 * @param user
 * @return gboolean
 */
gboolean insert_user(Users users, User user);

#endif
