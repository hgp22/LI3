#ifndef __UI_H__
#define __UI_H__

#include <glib.h>
#include <stdio.h>

typedef struct user *User;
typedef struct driver *Driver;
typedef struct taxi_system *TaxiSystem;

/**
 * @brief Prints result of query 1 for a user
 *
 * @param u Answer to query 1 for driver
 */
void show_query1_user(const User u);

/**
 * @brief Prints result of query 1 for a driver
 *
 * @param d Answer to query 1 for driver
 */
void show_query1_driver(const Driver d);

/**
 * @brief Prints result of query 2
 *
 * @param drivers Answer to query 2
 */
void show_query2(const GPtrArray *drivers);

/**
 * @brief Prints result of query 3
 *
 * @param users Answer to query 3
 */
void show_query3(const GPtrArray *users);

/**
 * @brief Prints result of query 4
 *
 * @param avg_score Answer to query 4
 */
void show_query4(double avg_score);

/**
 * @brief Prints result of query 5
 *
 * @param avg_cost Answer to query 5
 */
void show_query5(double avg_cost);

/**
 * @brief Prints result of query 6
 *
 * @param avg_distance Answer to query 6
 */
void show_query6(double avg_distance);

/**
 * @brief
 *
 * @param drivers
 * @param city
 */
void show_query7(const GPtrArray *drivers, const char *city);

/**
 * @brief
 *
 * @param rides
 * @param c
 */
void show_query8(const GPtrArray *rides, const TaxiSystem ts);

/**
 * @brief
 *
 * @param rides
 */
void show_query9(const GPtrArray *rides);

#endif
