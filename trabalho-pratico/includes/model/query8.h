#ifndef __QUERY8_H__
#define __QUERY8_H__

#include <glib.h>

typedef struct query8 *Query8;
typedef GHashTable *Users;
typedef GHashTable *Drivers;
typedef GPtrArray *Rides;

/**
 * @brief
 *
 * @param rides
 * @param users
 * @param drivers
 * @return Query8
 */
Query8 query8_new(Rides rides, Users users, Drivers drivers);

#endif
