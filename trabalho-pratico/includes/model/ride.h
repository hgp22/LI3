#ifndef __RIDE_H__
#define __RIDE_H__

#include <glib.h>

typedef struct ride *Ride;

/**
 * @brief Create new Ride
 *
 * @return Ride created
 */
Ride ride_new(void);

/**
 * @brief
 *
 * @param ride_record
 * @return Ride
 */
Ride ride_new_from_record(char *ride_record);

/**
 * @brief Set the ride id object
 *
 * @param r
 * @param id
 */
void ride_set_id(const Ride r, const char *id);

/**
 * @brief Set the ride date object
 *
 * @param r
 * @param date
 */
void ride_set_date(const Ride r, const char *date);

/**
 * @brief Set the ride driver object
 *
 * @param r
 * @param driver
 */
void ride_set_driver(const Ride r, const char *driver);

/**
 * @brief Set the ride user object
 *
 * @param r
 * @param user
 */
void ride_set_user(const Ride r, const char *user);

/**
 * @brief Set the ride city object
 *
 * @param r
 * @param city
 */
void ride_set_city(const Ride r, const char *city);

/**
 * @brief Set the ride distance object
 *
 * @param r
 * @param distance
 */
void ride_set_distance(const Ride r, const char *distance);

/**
 * @brief Set the ride score user object
 *
 * @param r
 * @param score_user
 */
void ride_set_score_user(const Ride r, const char *score_user);

/**
 * @brief Set the ride score driver object
 *
 * @param r
 * @param score_driver
 */
void ride_set_score_driver(const Ride r, const char *score_driver);

/**
 * @brief
 *
 * @param r
 * @param cost
 */
void ride_set_cost(const Ride r, double cost);

/**
 * @brief Set the ride tip object
 *
 * @param r
 * @param tip
 */
void ride_set_tip(const Ride r, const char *tip);

/**
 * @brief
 *
 * @param r
 * @param user_account_age
 */
void ride_set_user_account_age(const Ride r, guint16 user_account_age);

/**
 * @brief
 *
 * @param r
 * @param driver_account_age
 */
void ride_set_driver_account_age(const Ride r, guint16 driver_account_age);

/**
 * @brief Get the ride id object
 *
 * @param r
 * @return int
 */
int ride_get_id(const Ride r);

/**
 * @brief Get the ride date object
 *
 * @param r
 * @return guint16
 */
guint16 ride_get_date(const Ride r);

/**
 * @brief Get the ride driver object
 *
 * @param r
 * @return int
 */
int ride_get_driver(const Ride r);

/**
 * @brief Get the ride user object
 *
 * @param r
 * @return char*
 */
char *ride_get_user(const Ride r);

/**
 * @brief Get the ride city object
 *
 * @param r
 * @return char*
 */
char *ride_get_city(const Ride r);

/**
 * @brief Get the ride distance object
 *
 * @param r
 * @return double
 */
double ride_get_distance(const Ride r);

/**
 * @brief Get the ride score user object
 *
 * @param r
 * @return guint8
 */
guint8 ride_get_score_user(const Ride r);

/**
 * @brief Get the ride score driver object
 *
 * @param r
 * @return guint8
 */
guint8 ride_get_score_driver(const Ride r);

/**
 * @brief Get the ride cost object
 *
 * @param r
 * @return float
 */
double ride_get_cost(const Ride r);

/**
 * @brief Get the ride tip object
 *
 * @param r
 * @return float
 */
double ride_get_tip(const Ride r);

/**
 * @brief
 *
 * @param r
 * @return guint16
 */
guint16 ride_get_user_account_age(const Ride r);

/**
 * @brief
 *
 * @param r
 * @return guint16
 */
guint16 ride_get_driver_account_age(const Ride r);

/**
 * @brief
 *
 * @param r
 * @return char*
 */
char *ride_show_id(Ride r);

/**
 * @brief
 *
 * @param r
 * @return char*
 */
char *ride_show_date(Ride r);

/**
 * @brief
 *
 * @param r
 * @return char*
 */
char *ride_show_distance(Ride r);

/**
 * @brief
 *
 * @param r
 * @return char*
 */
char *ride_show_city(Ride r);

/**
 * @brief
 *
 * @param r
 * @return char*
 */
char *ride_show_tip(Ride r);

/**
 * @brief
 *
 * @param old_r
 * @return Ride
 */
Ride ride_copy(const Ride old_r);

/**
 * @brief Frees Ride
 *
 * @param ride Ride to be freed
 */
void ride_free(void *ride);

#endif
