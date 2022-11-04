#ifndef __QUERY3_H__
#define __QUERY3_H__

#include <glib.h>

typedef GPtrArray *Query3;
typedef GHashTable *Users;

/**
 * @brief
 *
 * @param drivers
 * @return Query3
 */
Query3 new_query3(Users users);

/**
 * @brief
 *
 * @param q3
 */
void free_query3(Query3 q3);

/**
 * @brief
 *
 * @param q3
 */
void free_query3_full(Query3 q3);

/**
 * @brief 
 * 
 * @param q3 
 */
void sort_query3(Query3 q3);

#endif
