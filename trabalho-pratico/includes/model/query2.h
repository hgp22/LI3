#ifndef __QUERY2_H__
#define __QUERY2_H__

#include <glib.h>

typedef GPtrArray *Query2;
typedef GHashTable *Drivers;
typedef struct driver *Driver;

/**
 * @brief Creates a new Query2
 *
 * @param drivers Drivers to create Query2
 * @return Query2 created
 */
Query2 query2_new(Drivers drivers);

/**
 * @brief Creates a sized Query2
 * 
 * @param N Sized of Query2
 * @return Query2 created
 */
Query2 query2_new_sized(int N);

/**
 * @brief Frees Query2
 *
 * @param q2 Query2 to be freed
 */
void query2_free(Query2 q2);

/**
 * @brief Adds a Driver to a Query2
 * 
 * @param q2 Query2 to add Driver
 * @param d Driver to be added
 */
void query2_add_driver(Query2 q2, Driver d);

/**
 * @brief Get Driver in index from Query2
 * 
 * @param q2 Query2 to get Driver
 * @param index Index to get in Query2
 * @return Driver in index
 */
Driver query2_index(Query2 q2, int index);

/**
 * @brief Sort Query2
 *
 * @param q2 Query2 to be sorted
 */
void query2_sort(Query2 q2);

#endif
