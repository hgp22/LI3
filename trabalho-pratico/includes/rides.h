#ifndef __RIDES_H__
#define __RIDES_H__

#include "ride.h"
#include <glib.h>

typedef GSList Rides;

/**
 * @brief 
 * 
 * @param rides 
 * @param ride 
 * @return Rides* 
 */
Rides *insert_ride(Rides *rides, Ride *ride);

#endif
