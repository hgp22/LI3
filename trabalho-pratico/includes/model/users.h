#ifndef __USERS_H__
#define __USERS_H__

#include <glib.h>

typedef struct user *User;
typedef struct catalog *Catalog;
typedef GHashTable *Users;

/**
 * @brief Creates a new Users
 *
 * @return Users created
 */
Users users_new(void);

/**
 * @brief Frees Users
 *
 * @param users Users freed
 */
void users_free(Users users);

/**
 * @brief Adds a User to Users
 *
 * @param users Users to add User
 * @param u User to add to Users
 * @return Control boolean
 */
gboolean users_add_user(Users users, User u);

/**
 * @brief Get a User from Users by username
 *
 * @param users Users to get User from
 * @param username Username to find User
 * @return User found
 */
User users_get_user(Users users, char *username);

/**
 * @brief Removes inactive users accounts in Users
 *
 * @param users Users to remove inactive accounts
 * @return Control integer
 */
guint users_remove_inactive_accounts(Users users);

#endif
