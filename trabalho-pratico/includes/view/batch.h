#ifndef __VIEW_BATCH_H__
#define __VIEW_BATCH_H__

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
void batch_print_query1_user(const User u, FILE *fp);

/**
 * @brief Prints result of query 1 for a driver
 *
 * @param d Answer to query 1 for driver
 */
void batch_print_query1_driver(const Driver d, FILE *fp);

/**
 * @brief Prints result of query 2
 *
 * @param drivers Answer to query 2
 */
void batch_print_query2(const GPtrArray *drivers, FILE *fp);

/**
 * @brief Prints result of query 3
 *
 * @param users Answer to query 3
 */
void batch_print_query3(const GPtrArray *users, FILE *fp);

/**
 * @brief Prints result of query 4
 *
 * @param avg_score Answer to query 4
 */
void batch_print_query4(double avg_score, FILE *fp);

/**
 * @brief Prints result of query 5
 *
 * @param avg_cost Answer to query 5
 */
void batch_print_query5(double avg_cost, FILE *fp);

/**
 * @brief Prints result of query 6
 *
 * @param avg_distance Answer to query 6
 */
void batch_print_query6(double avg_distance, FILE *fp);

/**
 * @brief
 *
 * @param drivers
 * @param city
 */
void batch_print_query7(const GPtrArray *drivers, const char *city, FILE *fp);

/**
 * @brief
 *
 * @param rides
 * @param c
 */
void batch_print_query8(const GPtrArray *rides, const TaxiSystem ts, FILE *fp);

/**
 * @brief
 *
 * @param rides
 */
void batch_print_query9(const GPtrArray *rides, FILE *fp);

#endif
