#ifndef __QUERY2_H__
#define __QUERY2_H__

#include <glib.h>

typedef GSList *Query2;
typedef GHashTable *Drivers;

/**
 * @brief 
 * 
 * @param drivers 
 * @return Query2 
 */
Query2 new_query2(Drivers drivers);

/**
 * @brief 
 * 
 * @param q2 
 */
void free_query2(Query2 q2);

/**
 * @brief 
 * 
 * @param q2 
 */
void free_query2_full(Query2 q2);

/**
 * @brief 
 * 
 * @param q2 
 * @return Query2 
 */
Query2 sort_query2(Query2 q2);

#endif
