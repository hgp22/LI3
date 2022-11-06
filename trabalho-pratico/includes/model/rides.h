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
 */
void free_rides(Rides rides);

/**
 * @brief
 *
 * @param rides
 * @param ride
 */
void add_rides_ride(Rides rides, Ride ride);

/**
 * @brief Get the rides ride object
 * 
 * @param rides 
 * @param index 
 * @return Ride 
 */
Ride get_rides_ride(Rides rides, guint index);

/**
 * @brief
 *
 * @param rides
 */
void sort_rides(Rides rides);

/**
 * @brief Get the rides avg something in range object
 *
 * @param rides
 * @param dateA
 * @param dateB
 * @param get_func
 * @return double
 */
double get_rides_avg_stat_in_range(Rides rides, char *dateA, char *dateB,
                                   double (*get_func)(Ride));

#endif
