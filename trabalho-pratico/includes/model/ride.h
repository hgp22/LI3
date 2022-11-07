#ifndef __RIDE_H__
#define __RIDE_H__

#include <stdint.h>

typedef struct driver *Driver;
typedef struct ride *Ride;

typedef enum field_ride {
    R_id,
    R_date,
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
 * @return Ride
 */
Ride ride_new(void);

/**
 * @brief
 *
 * @param ride
 */
void ride_free(Ride *r);

/**
 * @brief Set the ride id object
 *
 * @param r
 * @param id
 */
void ride_set_id(Ride r, char *id);

/**
 * @brief Set the ride date object
 *
 * @param r
 * @param date
 */
void ride_set_date(Ride r, char *date);

/**
 * @brief Set the ride driver object
 *
 * @param r
 * @param driver
 */
void ride_set_driver(Ride r, char *driver);

/**
 * @brief Set the ride user object
 *
 * @param r
 * @param user
 */
void ride_set_user(Ride r, char *user);

/**
 * @brief Set the ride city object
 *
 * @param r
 * @param city
 */
void ride_set_city(Ride r, char *city);

/**
 * @brief Set the ride distance object
 *
 * @param r
 * @param distance
 */
void ride_set_distance(Ride r, char *distance);

/**
 * @brief Set the ride score user object
 *
 * @param r
 * @param score_user
 */
void ride_set_score_user(Ride r, char *score_user);

/**
 * @brief Set the ride score driver object
 *
 * @param r
 * @param score_driver
 */
void ride_set_score_driver(Ride r, char *score_driver);

/**
 * @brief Set the ride cost object
 *
 * @param r
 * @param d
 */
void ride_set_cost(Ride r, Driver d);

/**
 * @brief Set the ride tip object
 *
 * @param r
 * @param tip
 */
void ride_set_tip(Ride r, char *tip);

/**
 * @brief Get the ride id object
 *
 * @param r
 * @return long
 */
long ride_get_id(Ride r);

/**
 * @brief Get the ride date object
 *
 * @param r
 * @return unsigned short
 */
unsigned short ride_get_date(Ride r);

/**
 * @brief Get the ride driver object
 *
 * @param r
 * @return long
 */
long ride_get_driver(Ride r);

/**
 * @brief Get the ride user object
 *
 * @param r
 * @return char*
 */
char *ride_get_user(Ride r);

/**
 * @brief Get the ride city object
 *
 * @param r
 * @return char*
 */
char *ride_get_city(Ride r);

/**
 * @brief Get the ride distance object
 *
 * @param r
 * @return double
 */
double ride_get_distance(Ride r);

/**
 * @brief Get the ride score user object
 *
 * @param r
 * @return uint8_t
 */
uint8_t ride_get_score_user(Ride r);

/**
 * @brief Get the ride score driver object
 *
 * @param r
 * @return uint8_t
 */
uint8_t ride_get_score_driver(Ride r);

/**
 * @brief Get the ride cost object
 *
 * @param r
 * @return float
 */
double ride_get_cost(Ride r);

/**
 * @brief Get the ride tip object
 *
 * @param r
 * @return float
 */
double ride_get_tip(Ride r);

/**
 * @brief
 *
 * @param old_r
 * @return Ride
 */
Ride copy_ride(Ride old_r);

#endif
