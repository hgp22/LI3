#ifndef __QUERY3_H__
#define __QUERY3_H__

#include <glib.h>

typedef struct catalog *Catalog;

typedef GSList *Query3;

/**
 * @brief
 *
 * @param c
 * @param N
 */
void query3(Catalog c, int N);

#endif
