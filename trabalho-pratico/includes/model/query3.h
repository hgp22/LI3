#ifndef __QUERY3_H__
#define __QUERY3_H__

#include <glib.h>

typedef GPtrArray *Query3;
typedef GHashTable *Users;
typedef struct user *User;

/**
 * @brief Creates a new Query3
 *
 * @param users Users to create Query3
 * @return Query3 created
 */
Query3 query3_new(Users users);

/**
 * @brief Creates a sized Query2
 * 
 * @param N Sized of Query2
 * @return Query3 created
 */
Query3 query3_new_sized(int N);

/**
 * @brief Frees Query3
 *
 * @param q3 Query3 to be freed
 */
void query3_free(Query3 q3);

/**
 * @brief Adds a User to a Query3
 * 
 * @param q3 Query3 to add User
 * @param u User to be added
 */
void query3_add_driver(Query3 q3, User u);

/**
 * @brief Get User in index from Query3
 * 
 * @param q3 Query3 to get Driver
 * @param index Index to get in Query3
 * @return User in index
 */
User query3_index(Query3 q3, int index);

/**
 * @brief Sort Query3
 *
 * @param q3 Query3 to be sorted
 */
void query3_sort(Query3 q3);

#endif
