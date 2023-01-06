#ifndef __TAXI_SYSTEM_H__
#define __TAXI_SYSTEM_H__

#include <glib.h>

typedef struct user *User;
typedef struct users *Users;
typedef struct driver *Driver;
typedef struct drivers *Drivers;
typedef struct rides *Rides;
typedef struct taxi_system *TaxiSystem;

/**
 * @brief Creates a new taxi_system
 *
 * @return TaxiSystem created
 */
TaxiSystem taxi_new(const char *inputs_path);

/**
 * @brief Get a user in taxi_system by username
 *
 * @param ts TaxiSystem to get user
 * @param username Username of user to be returned
 * @return User searched
 */
User taxi_get_user(const TaxiSystem ts, const char *username);

/**
 * @brief Get a driver in taxi_system by driver id
 *
 * @param ts TaxiSystem to get driver
 * @param id Id of driver to be returned
 * @return Driver searched
 */
Driver taxi_get_driver(const TaxiSystem ts, int id);

/**
 * @brief Get the top N drivers by score
 *
 * @param ts TaxiSystem to be searched
 * @param N Number of drivers to be returned
 * @return List of top N drivers by score
 */
GPtrArray *taxi_top_n_drivers_by_score(const TaxiSystem ts, int N);

/**
 * @brief Get the top N users by distanced travelled
 *
 * @param ts TaxiSystem to be searched
 * @param N Number of users to be returned
 * @return List of top N users by distance travelled
 */
GPtrArray *taxi_top_n_users_by_distance(const TaxiSystem ts, int N);

/**
 * @brief Get rides average cost in a city
 *
 * @param ts TaxiSystem
 * @param city City
 * @return Rides average cost in a city
 */
double taxi_city_avg_cost(const TaxiSystem ts, const char *city);

/**
 * @brief Get rides average cost between two dates inclusive
 *
 * @param ts TaxiSystem
 * @param dateA First date
 * @param dateB Second date
 * @return Average ride cost between two dates inclusive
 */
double taxi_avg_cost_in_range(const TaxiSystem ts, const char *dateA,
                              const char *dateB);

/**
 * @brief Get average distance travelled in a city between two dates inclusive
 *
 * @param ts TaxiSystem
 * @param city Cidade
 * @param dateA First date
 * @param dateB Second date
 * @return Average distance travelled in a city between two dates inclusive
 */
double taxi_city_avg_dist_in_range(const TaxiSystem ts, const char *city,
                                   const char *dateA, const char *dateB);

/**
 * @brief
 *
 * @param ts
 * @param city
 * @param N
 * @return GPtrArray
 */
GPtrArray *taxi_top_n_drivers_in_city(const TaxiSystem ts, const char *city,
                                      int N);

/**
 * @brief
 *
 * @param ts
 * @param gender
 * @param account_age
 * @return Rides
 */
GPtrArray *taxi_query8(const TaxiSystem ts, char gender, int account_age);

/**
 * @brief
 *
 * @param ts
 * @param dateA
 * @param dateB
 * @return Rides
 */
GPtrArray *taxi_rides_with_tip_in_range(const TaxiSystem ts, const char *dateA,
                                        const char *dateB);

/**
 * @brief Frees a taxi_system
 *
 * @param ts TaxiSystem to be freed
 */
void taxi_free(const TaxiSystem ts);

#endif
