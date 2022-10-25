#ifndef __RIDES_H__
#define __RIDES_H__

#include "user.h"
#include <stdint.h>

typedef struct query1 *Query1;

/**
 * @brief
 *
 * @param u
 * @return Query1
 */
Query1 init_query1(User u);

/**
 * @brief
 *
 * @param q
 * @param score
 */
void add_score(Query1 q, unsigned short score);

/**
 * @brief
 *
 * @param q
 */
void add_trip(Query1 q);

/**
 * @brief
 *
 * @param q
 * @param money
 */
void add_money(Query1 q, int money);

/**
 * @brief
 *
 * @param q
 * @return char*
 */
char *query1_to_string(Query1 q);

#endif
