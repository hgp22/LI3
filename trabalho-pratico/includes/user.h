#ifndef __USER_H__
#define __USER_H__

#include <glib.h>
#include <stdint.h>

typedef struct user *User;

typedef struct ride *Ride;

typedef enum field_user {
    U_username,
    U_name,
    U_gender,
    U_birth_date,
    U_account_creation,
    U_pay_method,
    U_account_status,
} Field_user;

typedef enum account_status Status;

/**
 * @brief
 *
 * @return User
 */
User new_user(void);

/**
 * @brief
 *
 * @param user
 */
void free_user(void *user);

/**
 * @brief Set the username object
 *
 * @param u
 * @param username
 */
void set_user_username(User u, char *username);

/**
 * @brief Set the user name object
 *
 * @param u
 * @param name
 */
void set_user_name(User u, char *name);

/**
 * @brief Set the user gender object
 *
 * @param u
 * @param gender
 */
void set_user_gender(User u, char *gender);

/**
 * @brief Set the user age object
 *
 * @param u
 * @param birth_date
 */
void set_user_age(User u, char *birth_date);

/**
 * @brief Set the user account age object
 *
 * @param u
 * @param account_creation
 */
void set_user_account_age(User u, char *account_creation);

/**
 * @brief Set the user account status object
 *
 * @param u
 * @param account_status
 */
void set_user_account_status(User u, char *account_status);

/**
 * @brief Get the user name object
 *
 * @param u
 * @return char*
 */
char *get_user_name(User u);

/**
 * @brief Get the user username object
 *
 * @param u
 * @return char*
 */
char *get_user_username(User u);

/**
 * @brief Get the user gender object
 *
 * @param u
 * @return char
 */
char get_user_gender(User u);

/**
 * @brief Get the user age object
 *
 * @param u
 * @return uint8_t
 */
uint8_t get_user_age(User u);

/**
 * @brief Get the user account age object
 *
 * @param u
 * @return unsigned short
 */
unsigned short get_user_account_age(User u);

/**
 * @brief Get the user avg score object
 *
 * @param u
 * @return float
 */
float get_user_avg_score(User u);

/**
 * @brief Get the user total spent object
 *
 * @param u
 * @return float
 */
float get_user_total_spent(User u);

/**
 * @brief Get the user total distance object
 *
 * @param u
 * @return int
 */
int get_user_total_distance(User u);

/**
 * @brief Get the user n trips object
 *
 * @param u
 * @return float
 */
float get_user_n_trips(User u);

/**
 * @brief Get the user trip dates object
 *
 * @param u
 * @return GSList*
 */
GSList *get_user_trip_dates(User u);

/**
 * @brief Get the user account status object
 *
 * @param u
 * @return Status
 */
Status get_user_account_status(User u);

/**
 * @brief
 *
 * @param u
 * @param r
 */
void add_user_ride_data(User u, Ride r);

/**
 * @brief
 *
 * @param u
 * @param r
 */
void add_user_ride_data(User u, Ride r);

#endif
