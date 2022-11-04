#ifndef __UI_H__
#define __UI_H__

#include <glib.h>

typedef struct user *User;
typedef struct driver *Driver;
typedef GPtrArray *Query2;
typedef GSList *Query3;

/**
 * @brief
 *
 * @param u
 */
void show_query1_user(User u);

/**
 * @brief
 *
 * @param d
 */
void show_query1_driver(Driver d);

/**
 * @brief
 *
 * @param q2
 */
void show_query2(Query2 q2);

/**
 * @brief
 *
 * @param q3
 */
void show_query3(Query3 q3);

/**
 * @brief
 *
 * @param avg_score
 */
void show_query4(double avg_score);

#endif
