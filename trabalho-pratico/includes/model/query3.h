#ifndef __QUERY3_H__
#define __QUERY3_H__

#include <glib.h>

typedef GPtrArray *Query3;
typedef GHashTable *Users;

/**
 * @brief Creat new Query3
 *
 * @param users Users to creat Query3
 * @return Query3 created
 */
Query3 query3_new(Users users);

/**
 * @brief Free Query3
 *
 * @param q3 Query3 to be freed
 */
void query3_free(Query3 q3);

/**
 * @brief Free Query3 and it's elements
 *
 * @param q3 Query3 to be fully freed
 */
void query3_free_full(Query3 q3);

/**
 * @brief Sort Query3
 *
 * @param q3 Query3 to be sorted
 */
void query3_sort(Query3 q3);

#endif
