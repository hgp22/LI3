#ifndef __RIDES_H__
#define __RIDES_H__

#include <glib.h>

typedef struct ride *Ride;
typedef GArray *Rides;

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

/**
 * @brief Get the ride avg cost in range object
 *
 * @param rides
 * @param dateA
 * @param dateB
 * @return double
 */
double get_rides_avg_cost_in_range(Rides rides, char *dateA, char *dateB);

/**
 * @brief Get the ride avg distance in range object
 * 
 * @param rides 
 * @param dateA 
 * @param dateB 
 * @return double 
 */
double get_rides_avg_distance_in_range(Rides rides, char *dateA, char *dateB);

#endif
