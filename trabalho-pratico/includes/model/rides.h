#ifndef __RIDES_H__
#define __RIDES_H__

#include <glib.h>

typedef struct ride *Ride;
typedef struct rides *Rides;

/**
 * @brief Creates a new Rides
 *
 * @return Rides created
 */
Rides rides_new(void);

/**
 * @brief
 *
 * @param inputs_path
 * @return Rides
 */
Rides rides_new_from_file(const char *inputs_path);

/**
 * @brief
 *
 * @param rides
 */
void rides_new_genders(const Rides rides);

/**
 * @brief Adds a Ride to Rides
 *
 * @param rides Rides to add Ride
 * @param ride Ride to add to Rides
 */
void rides_add_ride(const Rides rides, const Ride ride);

/**
 * @brief
 *
 * @param rides
 * @param ride_record
 */
void rides_add_record(const Rides rides, const char *ride_record);

/**
 * @brief
 *
 * @param rides
 * @param ride
 * @param index
 */
void rides_replace_ride(const Rides rides, const Ride ride, guint index);

/**
 * @brief Get Ride from Rides
 *
 * @param rides Rides to get Ride from
 * @param index Index to get Ride from
 * @return Ride found
 */
Ride rides_get_ride(const Rides rides, guint index);

/**
 * @brief
 *
 * @param rides
 * @return guint
 */
guint rides_size(const Rides rides);

/**
 * @brief
 *
 * @param rides
 * @param index
 * @param cost
 */
void rides_set_ride_cost(const Rides rides, guint index, double cost);

/**
 * @brief
 *
 * @param rides
 * @param index
 * @param user_account_age
 */
void rides_set_ride_user_account_age(const Rides rides, guint index,
                                     guint16 user_account_age);

/**
 * @brief
 *
 * @param rides
 * @param index
 * @param driver_account_age
 */
void rides_set_ride_driver_account_age(const Rides rides, guint index,
                                       guint16 driver_account_age);

/**
 * @brief
 *
 * @param rides
 * @param index
 * @return guint16
 */
guint16 rides_get_ride_date(const Rides rides, guint index);

/**
 * @brief
 *
 * @param rides
 * @param index
 * @return char*
 */
char *rides_get_ride_user(const Rides rides, guint index);

/**
 * @brief
 *
 * @param rides
 * @param index
 * @return int
 */
int rides_get_ride_driver(const Rides rides, guint index);

/**
 * @brief
 *
 * @param rides
 * @param index
 * @return char*
 */
char *rides_get_ride_city(const Rides rides, guint index);

/**
 * @brief
 *
 * @param rides
 * @param index
 * @return guint8
 */
guint8 rides_get_ride_distance(const Rides rides, guint index);

/**
 * @brief
 *
 * @param rides
 * @param index
 * @return guint8
 */
guint8 rides_get_ride_score_user(const Rides rides, guint index);

/**
 * @brief
 *
 * @param rides
 * @param index
 * @return guint8
 */
guint8 rides_get_ride_score_driver(const Rides rides, guint index);

/**
 * @brief
 *
 * @param rides
 * @param index
 * @return double
 */
double rides_get_ride_tip(const Rides rides, guint index);

/**
 * @brief
 *
 * @param rides
 * @param index
 */
void rides_add_females_ride_index(const Rides rides, guint index);

/**
 * @brief
 *
 * @param rides
 * @param index
 */
void rides_add_males_ride_index(const Rides rides, guint index);

/**
 * @brief Sorts Rides
 *
 * @param rides Rides sorted
 */
Rides rides_sort_date(const Rides rides);

/**
 * @brief Sorts Rides
 *
 * @param rides Rides sorted
 */
Rides rides_sort_accounts_age(const Rides rides);

/**
 * @brief Get rides with tip
 *
 * @param rides Rides to filter
 * @return Rides with tips
 */
Rides rides_with_tip(const Rides rides);

/**
 * @brief
 *
 * @param rides
 * @return Rides
 */
Rides rides_cities(const Rides rides);

/**
 * @brief Get the average ride statistic between two dates
 *
 * @param rides GPtrArray
 * @param dateA First date
 * @param dateB Second date
 * @param get_func Function to get stat
 * @return Calculated average
 */
double rides_get_avg_stat_in_range(const GPtrArray *rides, const char *dateA,
                                   const char *dateB, double (*get_func)(Ride));

/**
 * @brief
 *
 * @param rides
 * @param city_name
 * @return double
 */
double rides_city_avg_cost(const Rides rides, const char *city_name);

/**
 * @brief
 *
 * @param rides
 * @param dateA
 * @param dateB
 * @return double
 */
double rides_get_avg_cost_in_range(const Rides rides, const char *dateA,
                                   const char *dateB);

/**
 * @brief
 *
 * @param rides
 * @param city_name
 * @param dateA
 * @param dateB
 * @return double
 */
double rides_city_avg_dist_in_range(const Rides rides, const char *city_name,
                                    const char *dateA, const char *dateB);

/**
 * @brief
 *
 * @param rides
 * @param gender
 * @param account_age
 * @return GPtrArray*
 */
GPtrArray *rides_by_gender_by_age(const Rides rides, char gender,
                                  int account_age);

/**
 * @brief Get rides with tip between two date
 *
 * @param rides Rides to process
 * @param dateA First date
 * @param dateB Second date
 * @return Rides with tip bewtween two date
 */
GPtrArray *rides_get_rides_with_tip_in_range(const Rides rides,
                                             const char *dateA,
                                             const char *dateB);

/**
 * @brief Frees Rides
 *
 * @param rides Rides to be freed
 */
void rides_free(const Rides rides);

#endif
