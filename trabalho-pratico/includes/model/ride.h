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
Ride new_ride(void);

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
void set_ride_id(Ride r, char *id);

/**
 * @brief Set the ride date object
 *
 * @param r
 * @param date
 */
void set_ride_date(Ride r, char *date);

/**
 * @brief Set the ride driver object
 *
 * @param r
 * @param driver
 */
void set_ride_driver(Ride r, char *driver);

/**
 * @brief Set the ride user object
 *
 * @param r
 * @param user
 */
void set_ride_user(Ride r, char *user);

/**
 * @brief Set the ride city object
 *
 * @param r
 * @param city
 */
void set_ride_city(Ride r, char *city);

/**
 * @brief Set the ride distance object
 *
 * @param r
 * @param distance
 */
void set_ride_distance(Ride r, char *distance);

/**
 * @brief Set the ride score user object
 *
 * @param r
 * @param score_user
 */
void set_ride_score_user(Ride r, char *score_user);

/**
 * @brief Set the ride score driver object
 *
 * @param r
 * @param score_driver
 */
void set_ride_score_driver(Ride r, char *score_driver);

/**
 * @brief Set the ride cost object
 *
 * @param r
 * @param d
 */
void set_ride_cost(Ride r, Driver d);

/**
 * @brief Set the ride tip object
 *
 * @param r
 * @param tip
 */
void set_ride_tip(Ride r, char *tip);

/**
 * @brief Get the ride id object
 *
 * @param r
 * @return long
 */
long get_ride_id(Ride r);

/**
 * @brief Get the ride date object
 *
 * @param r
 * @return unsigned short
 */
unsigned short get_ride_date(Ride r);

/**
 * @brief Get the ride driver object
 *
 * @param r
 * @return long
 */
long get_ride_driver(Ride r);

/**
 * @brief Get the ride user object
 *
 * @param r
 * @return char*
 */
char *get_ride_user(Ride r);

/**
 * @brief Get the ride city object
 *
 * @param r
 * @return char*
 */
char *get_ride_city(Ride r);

/**
 * @brief Get the ride distance object
 *
 * @param r
 * @return uint8_t
 */
uint8_t get_ride_distance(Ride r);

/**
 * @brief Get the ride score user object
 *
 * @param r
 * @return uint8_t
 */
uint8_t get_ride_score_user(Ride r);

/**
 * @brief Get the ride score driver object
 *
 * @param r
 * @return uint8_t
 */
uint8_t get_ride_score_driver(Ride r);

/**
 * @brief Get the ride cost object
 *
 * @param r
 * @return float
 */
double get_ride_cost(Ride r);

/**
 * @brief Get the ride tip object
 *
 * @param r
 * @return float
 */
double get_ride_tip(Ride r);

/**
 * @brief 
 * 
 * @param old_r 
 * @return Ride 
 */
Ride copy_ride(Ride old_r);

#endif
