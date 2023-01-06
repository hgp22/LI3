#ifndef __USER_H__
#define __USER_H__

#include <glib.h>

typedef struct user *User;

/**
 * @brief Create new User
 *
 * @return User created
 */
User user_new(void);

/**
 * @brief
 *
 * @param user_record
 * @return User
 */
User user_new_from_record(const char *user_record);

/**
 * @brief Set the user username object
 *
 * @param u
 * @param username
 */
void user_set_username(const User u, const char *username);

/**
 * @brief Set the user name object
 *
 * @param u
 * @param name
 */
void user_set_name(const User u, const char *name);

/**
 * @brief Set the user gender object
 *
 * @param u
 * @param gender
 */
void user_set_gender(const User u, const char *gender);

/**
 * @brief Set the user age object
 *
 * @param u
 * @param birth_date
 */
void user_set_age(const User u, const char *birth_date);

/**
 * @brief Set the user account age object
 *
 * @param u
 * @param account_creation
 */
void user_set_account_age(const User u, const char *account_creation);

/**
 * @brief Get the user username object
 *
 * @param u
 * @return char*
 */
char *user_get_username(const User u);

/**
 * @brief Get the user name object
 *
 * @param u
 * @return char*
 */
char *user_get_name(const User u);

/**
 * @brief Get the user gender object
 *
 * @param u
 * @return char
 */
char user_get_gender(const User u);

/**
 * @brief Get the user age object
 *
 * @param u
 * @return guint8
 */
guint8 user_get_age(const User u);

/**
 * @brief Get the user account age object
 *
 * @param u
 * @return guint16
 */
guint16 user_get_account_age(const User u);

/**
 * @brief Get the user avg score object
 *
 * @param u
 * @return double
 */
double user_get_avg_score(const User u);

/**
 * @brief Get the user total spent object
 *
 * @param u
 * @return double
 */
double user_get_total_spent(const User u);

/**
 * @brief Get the user total distance object
 *
 * @param u
 * @return guint16
 */
guint16 user_get_total_distance(const User u);

/**
 * @brief Get the user n trips object
 *
 * @param u
 * @return guint16
 */
guint16 user_get_n_trips(const User u);

/**
 * @brief Get the user last ride date object
 *
 * @param u
 * @return guint16
 */
guint16 user_get_last_ride_date(const User u);

/**
 * @brief
 *
 * @param u
 * @param score
 * @param cost
 * @param tip
 * @param date
 * @param distance
 */
void user_add_ride_data(const User u, guint8 score, double cost, guint16 date,
                        guint8 distance);

/**
 * @brief
 *
 * @param old_u
 * @return User
 */
User user_copy(const User old_u);

/**
 * @brief Frees User
 *
 * @param user User to be freed
 */
void user_free(void *user);

#endif
