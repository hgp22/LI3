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
Rides rides_new(void);

/**
 * @brief
 *
 * @param rides
 */
void rides_free(Rides rides);

/**
 * @brief
 *
 * @param rides
 * @param ride
 */
void rides_add_ride(Rides rides, Ride ride);

/**
 * @brief 
 * 
 * @param rides 
 * @param index 
 * @return Ride 
 */
Ride rides_get_ride(Rides rides, guint index);

/**
 * @brief
 *
 * @param rides
 */
void rides_sort(Rides rides);

/**
 * @brief Get the rides avg something in range object
 *
 * @param rides
 * @param dateA
 * @param dateB
 * @param get_func
 * @return double
 */
double rides_get_avg_stat_in_range(Rides rides, char *dateA, char *dateB, double (*get_func)(Ride));

#endif
