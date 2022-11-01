#ifndef __QUERY3_H__
#define __QUERY3_H__

#include "user.h"
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

/**
 * @brief
 *
 * @param u
 * @return char*
 */
static char *_user_to_q3_string(User u);

#endif
