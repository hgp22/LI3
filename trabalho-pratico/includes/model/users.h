#ifndef __USERS_H__
#define __USERS_H__

#include <glib.h>

typedef struct user *User;
typedef struct catalog *Catalog;
typedef GHashTable *Users;

/**
 * @brief Create new Users
 *
 * @return Users
 */
Users users_new(void);

/**
 * @brief Frees Users
 *
 * @param users
 */
void users_free(Users users);

/**
 * @brief
 *
 * @param users
 * @param u
 * @return gboolean
 */
gboolean users_add_user(Users users, User u);

/**
 * @brief Get the user object
 *
 * @param users
 * @param username
 * @return User
 */
User users_get_user(Users users, char *username);

/**
 * @brief
 *
 * @param users
 * @return guint
 */
guint users_remove_inactive_accounts(Users users);

#endif
