#ifndef __RIDES_H__
#define __RIDES_H__

#include <glib.h>

typedef struct ride *Ride;
typedef GPtrArray *Rides;

/**
 * @brief 
 * 
 * @return Rides 
 */
Rides new_rides(void);

/**
 * @brief 
 * 
 * @param rides 
 * @param ride 
 */
void add_ride(Rides rides, Ride ride);

/**
 * @brief
 *
 * @param rides
 */
void free_rides(Rides rides);

/**
 * @brief 
 * 
 * @param rides 
 */
void sort_rides(Rides rides);

#endif
