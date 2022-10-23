#ifndef __USER_H__
#define __USER_H__

typedef struct user *User;

typedef enum field_user {
    U_username,
    U_name,
    U_gender,
    U_birth_date,
    U_account_creation,
    U_pay_method,
    U_account_status,
} Field_user;

typedef enum gender {
    Male,
    Female,
} Gender;

/**
 * @brief
 *
 * @return User
 */
User init_user(void);

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
 * @brief Set the user birth date object
 *
 * @param u
 * @param birth_date
 */
void set_user_birth_date(User u, char *birth_date);

/**
 * @brief Set the user account creation object
 *
 * @param u
 * @param account_creation
 */
void set_user_account_creation(User u, char *account_creation);

/**
 * @brief Set the user pay method object
 *
 * @param u
 * @param pay_method
 */
void set_user_pay_method(User u, char *pay_method);

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
 * @brief Get the user name object
 *
 * @param u
 * @return char*
 */
char *get_user_username(User u);

/**
 * @brief Get the user gender object
 *
 * @param u
 * @return Gender
 */
Gender get_user_gender(User u);

/**
 * @brief Get the user name object
 *
 * @param u
 * @return char*
 */
char *get_user_birth_date(User u);

/**
 * @brief Get the user name object
 *
 * @param u
 * @return char*
 */
char *get_user_account_creation(User u);

/**
 * @brief Get the user name object
 *
 * @param u
 * @return char*
 */
char *get_user_pay_method(User u);

/**
 * @brief Get the user name object
 *
 * @param u
 * @return char*
 */
char *get_user_account_status(User u);

#endif
