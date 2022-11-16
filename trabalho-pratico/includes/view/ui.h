#ifndef __UI_H__
#define __UI_H__

#include <glib.h>
#include <stdio.h>

typedef struct user *User;
typedef struct driver *Driver;
typedef GPtrArray *Query2;
typedef GPtrArray *Query3;
typedef GPtrArray *Query9;

/**
 * @brief Sets next output file
 *
 * @return FILE* File pointer to next output file
 */
FILE *next_output_file(void);

/**
 * @brief Prints result of query 1 for a user
 *
 * @param u Answer to query 1 for driver
 */
void show_query1_user(User u);

/**
 * @brief Prints result of query 1 for a driver
 *
 * @param d Answer to query 1 for driver
 */
void show_query1_driver(Driver d);

/**
 * @brief Prints result of query 2
 *
 * @param q2 Answer to query 2
 */
void show_query2(Query2 q2);

/**
 * @brief Prints result of query 3
 *
 * @param q3 Answer to query 3
 */
void show_query3(Query3 q3);

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
void show_query7(Query2 drivers, char *city);

/**
 * @brief
 *
 * @param q9
 */
void show_query9(Query9 q9);

#endif
