#ifndef __USERS_H__
#define __USERS_H__

#include <glib.h>

typedef struct user *User;
typedef struct users *Users;

/**
 * @brief Creates a new Users
 *
 * @return Users created
 */
Users users_new(void);

/**
 * @brief
 *
 * @param inputs_path
 * @return Users
 */
Users users_new_from_file(const char *inputs_path);

/**
 * @brief Adds a User to Users
 *
 * @param users Users to add User
 * @param u User to add to Users
 * @return Control boolean
 */
gboolean users_add_user(const Users users, const User u);

/**
 * @brief
 *
 * @param users
 * @param user_record
 */
void users_add_record(const Users users, const char *user_record);

/**
 * @brief Get a User from Users by username
 *
 * @param users Users to get User from
 * @param username Username to find User
 * @return User found
 */
User users_get_user(const Users users, const char *username);

/**
 * @brief
 *
 * @param users
 * @param username
 * @param score
 * @param cost
 * @param tip
 * @param date
 * @param distance
 */
void users_add_user_ride_data(const Users users, const char *username,
                              guint8 score, double cost, guint16 date,
                              guint8 distance);

/**
 * @brief
 *
 * @param users
 * @param username
 * @return char
 */
char users_get_user_gender(const Users users, const char *username);

/**
 * @brief
 *
 * @param users
 * @param username
 * @return guint16
 */
guint16 users_get_user_account_age(const Users users, const char *username);

/**
 * @brief
 *
 * @param users
 * @param username
 * @return int
 */
int users_has_user(const Users users, const char *username);

/**
 * @brief Populate users array
 *
 * @param users Users to populate
 * @return Users
 */
Users users_list(const Users users);

/**
 * @brief Returns the top N users in users
 *
 * @param users Users
 * @param N Number of users
 * @return Top N users
 */
GPtrArray *users_top_n_users(const Users users, int N);

/**
 * @brief Frees Users
 *
 * @param users Users freed
 */
void users_free(const Users users);

#endif
