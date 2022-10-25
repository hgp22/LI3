#ifndef __CATALOG2_H__
#define __CATALOG2_H__

#include "catalog.h"

typedef struct catalog2 *Catalog2;

/**
 * @brief 
 * 
 * @param c 
 * @return Catalog2 
 */
Catalog2 init_catalog2(Catalog c);

/**
 * @brief 
 * 
 * @param user 
 * @param hash 
 */
void insert_user_hash(gpointer user, gpointer hash);

/**
 * @brief 
 * 
 * @param ride 
 * @param query1 
 */
void update_query1(gpointer ride, gpointer query1);

#endif
