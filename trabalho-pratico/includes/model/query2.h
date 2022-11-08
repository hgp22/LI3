#ifndef __QUERY2_H__
#define __QUERY2_H__

#include <glib.h>

typedef GPtrArray *Query2;
typedef GHashTable *Drivers;
typedef struct driver *Driver;

/**
 * @brief Creat a new Query2
 *
 * @param drivers Drivers to creat Query2
 * @return Query2
 */
Query2 query2_new(Drivers drivers);

/**
 * @brief 
 * 
 * @param N 
 * @return Query2 
 */
Query2 query2_new_sized(int N);

/**
 * @brief Free Query2
 *
 * @param q2 Query2 to be freed
 */
void query2_free(Query2 q2);

/**
 * @brief 
 * 
 * @param q2 
 * @param d 
 */
void query2_add_driver(Query2 q2, Driver d);

/**
 * @brief 
 * 
 * @param q2 
 * @param index 
 * @return Driver 
 */
Driver query2_index(Query2 q2, int index);

/**
 * @brief Sort Query2
 *
 * @param q2 Query2 to be sorted
 */
void query2_sort(Query2 q2);

#endif
