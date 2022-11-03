#ifndef __RIDES_H__
#define __RIDES_H__

#include <glib.h>

typedef struct ride *Ride;
typedef GSList *Rides;

/**
 * @brief
 *
 * @param rides
 * @param ride
 * @return Rides
 */
Rides insert_ride(Rides rides, Ride ride);

/**
 * @brief 
 * 
 * @param rides 
 */
void free_rides(Rides rides);

#endif
