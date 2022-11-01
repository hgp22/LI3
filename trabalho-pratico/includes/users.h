#ifndef __USERS_H__
#define __USERS_H__

#include "user.h"
#include <glib.h>

typedef GHashTable *Users;

typedef struct catalog *Catalog;

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
User get_user(Users users, char *username);

/**
 * @brief
 *
 * @param users
 * @return guint
 */
guint remove_inactive_users(Users users);

/**
 * @brief
 *
 * @param key
 * @param value
 * @param user_data
 * @return gboolean
 */
static gboolean _clean(gpointer key, gpointer value, gpointer user_data);

/**
 * @brief
 *
 * @param data
 */
static void _key_destroyed(gpointer data);

/**
 * @brief
 *
 * @param data
 */
static void _value_destroyed(gpointer data);

#endif
