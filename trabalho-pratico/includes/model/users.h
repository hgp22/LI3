#ifndef __USERS_H__
#define __USERS_H__

#include <glib.h>

typedef struct user *User;
typedef struct catalog *Catalog;
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
 */
void free_users(Users users);

/**
 * @brief
 *
 * @param users
 * @param u
 * @return gboolean
 */
gboolean insert_user(Users users, User u);

/**
 * @brief Get the user object
 *
 * @param users
 * @param username
 * @return User
 */
User get_users_user(Users users, char *username);

/**
 * @brief
 *
 * @param users
 * @return guint
 */
guint remove_inactive_users(Users users);

#endif
