#ifndef __RIDE_H__
#define __RIDE_H__

typedef struct ride Ride;

typedef enum field_ride {
    R_id,
    R_state,
    R_driver,
    R_user,
    R_city,
    R_distance,
    R_score_user,
    R_score_driver,
    R_tip,
    R_comment,
} Field_ride;

/**
 * @brief
 *
 * @return Ride*
 */
Ride *init_ride(void);

/**
 * @brief
 *
 * @param ride
 */
void free_ride(void *ride);

/**
 * @brief Set the ride id object
 *
 * @param r
 * @param id
 */
void set_ride_id(Ride *r, char *id);

/**
 * @brief Set the ride state object
 *
 * @param r
 * @param state
 */
void set_ride_state(Ride *r, char *state);

/**
 * @brief Set the ride driver object
 *
 * @param r
 * @param driver
 */
void set_ride_driver(Ride *r, char *driver);

/**
 * @brief Set the ride user object
 *
 * @param r
 * @param user
 */
void set_ride_user(Ride *r, char *user);

/**
 * @brief Set the ride city object
 *
 * @param r
 * @param city
 */
void set_ride_city(Ride *r, char *city);

/**
 * @brief Set the ride distance object
 *
 * @param r
 * @param distance
 */
void set_ride_distance(Ride *r, char *distance);

/**
 * @brief Set the ride score user object
 *
 * @param r
 * @param score_user
 */
void set_ride_score_user(Ride *r, char *score_user);

/**
 * @brief Set the ride score driver object
 *
 * @param r
 * @param score_driver
 */
void set_ride_score_driver(Ride *r, char *score_driver);

/**
 * @brief Set the ride tip object
 *
 * @param r
 * @param tip
 */
void set_ride_tip(Ride *r, char *tip);

/**
 * @brief Set the ride comment object
 *
 * @param r
 * @param comment
 */
void set_ride_comment(Ride *r, char *comment);

/**
 * @brief Get the user name object
 *
 * @param u
 * @return char*
 */
char *get_ride_id(Ride *r);

/**
 * @brief Get the user name object
 *
 * @param u
 * @return char*
 */
char *get_ride_state(Ride *r);

/**
 * @brief Get the user name object
 *
 * @param u
 * @return char*
 */
char *get_ride_driver(Ride *r);

/**
 * @brief Get the user name object
 *
 * @param u
 * @return char*
 */
char *get_ride_user(Ride *r);

/**
 * @brief Get the user name object
 *
 * @param u
 * @return char*
 */
char *get_ride_city(Ride *r);

/**
 * @brief Get the user name object
 *
 * @param u
 * @return char*
 */
char *get_ride_distance(Ride *r);

/**
 * @brief Get the user name object
 *
 * @param u
 * @return char*
 */
char *get_ride_score_user(Ride *r);

/**
 * @brief Get the user name object
 *
 * @param u
 * @return char*
 */
char *get_ride_score_driver(Ride *r);

/**
 * @brief Get the user name object
 *
 * @param u
 * @return char*
 */
char *get_ride_tip(Ride *r);

/**
 * @brief Get the user name object
 *
 * @param u
 * @return char*
 */
char *get_ride_comment(Ride *r);

#endif
