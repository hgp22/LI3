#ifndef __QUERY3_H__
#define __QUERY3_H__

#include <glib.h>

typedef GPtrArray *Query3;
typedef GHashTable *Users;
typedef struct user *User;

/**
 * @brief Creat new Query3
 *
 * @param users Users to creat Query3
 * @return Query3 created
 */
Query3 query3_new(Users users);

/**
 * @brief 
 * 
 * @param N 
 * @return Query3 
 */
Query3 query3_new_sized(int N);

/**
 * @brief Free Query3
 *
 * @param q3 Query3 to be freed
 */
void query3_free(Query3 q3);

/**
 * @brief 
 * 
 * @param q3 
 * @param u 
 */
void query3_add_driver(Query3 q3, User u);

/**
 * @brief 
 * 
 * @param q3 
 * @param index 
 * @return User
 */
User query3_index(Query3 q3, int index);

/**
 * @brief Sort Query3
 *
 * @param q3 Query3 to be sorted
 */
void query3_sort(Query3 q3);

#endif
