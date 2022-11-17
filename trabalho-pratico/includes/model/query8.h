#ifndef __QUERY8_H__
#define __QUERY8_H__

#include <glib.h>

typedef struct query8 *Query8;
typedef GHashTable *Users;
typedef GHashTable *Drivers;
typedef GPtrArray *Rides;

/**
 * @brief
 *
 * @param rides
 * @param users
 * @param drivers
 * @return Query8
 */
Query8 query8_new(Rides rides, Users users, Drivers drivers);

/**
 * @brief
 *
 * @param q8
 */
void query8_free(Query8 q8);

/**
 * @brief 
 * 
 * @param q8 
 * @param gender 
 * @param account_age 
 * @return Rides 
 */
Rides query8_get_answer(Query8 q8, char gender, int account_age);

#endif
