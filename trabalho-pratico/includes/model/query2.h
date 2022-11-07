#ifndef __QUERY2_H__
#define __QUERY2_H__

#include <glib.h>

typedef GPtrArray *Query2;
typedef GHashTable *Drivers;

/**
 * @brief Creat a new Query2
 *
 * @param drivers Drivers to creat Query2
 * @return Query2
 */
Query2 query2_new(Drivers drivers);

/**
 * @brief Free Query2
 *
 * @param q2 Query2 to be freed
 */
void query2_free(Query2 q2);

/**
 * @brief Sort Query2
 *
 * @param q2 Query2 to be sorted
 */
void query2_sort(Query2 q2);

#endif
