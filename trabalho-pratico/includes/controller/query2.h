#ifndef __QUERY2_H__
#define __QUERY2_H__

#include <glib.h>

typedef struct catalog *Catalog;

typedef GSList *Query2;

/**
 * @brief
 *
 * @param c
 * @param N
 */
void query2(Catalog c, int N);

#endif
