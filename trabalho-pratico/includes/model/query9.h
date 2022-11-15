#ifndef __QUERY9_H__
#define __QUERY9_H__

#include <glib.h>

typedef GPtrArray *Query9;
typedef GPtrArray *Rides;

/**
 * @brief 
 * 
 * @param rides 
 * @return Query9 
 */
Query9 query9_new(Rides rides);

#endif
