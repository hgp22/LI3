#ifndef __RIDES_H__
#define __RIDES_H__

#include <glib.h>

typedef struct ride *Ride;
typedef GPtrArray *Rides;

/**
 * @brief Creates a new Rides
 *
 * @return Rides created
 */
Rides rides_new(void);

/**
 * @brief Frees Rides
 *
 * @param rides Rides to be freed
 */
void rides_free(Rides rides);

/**
 * @brief Adds a Ride to Rides
 *
 * @param rides Rides to add Ride
 * @param ride Ride to add to Rides
 */
void rides_add_ride(Rides rides, Ride ride);

/**
 * @brief
 *
 * @param rides
 * @param ride
 * @param index
 */
void rides_replace_ride(Rides rides, Ride ride, guint index);

/**
 * @brief Get Ride from Rides
 *
 * @param rides Rides to get Ride from
 * @param index Index to get Ride from
 * @return Ride found
 */
Ride rides_get_ride(Rides rides, guint index);

/**
 * @brief Get shallow Ride from Rides
 *
 * @param rides Rides to get Ride from
 * @param index Index to get Ride from
 * @return Ride found
 */
Ride rides_get_ride_shallow(Rides rides, guint index);

/**
 * @brief Sorts Rides
 *
 * @param rides Rides sorted
 */
void rides_sort(Rides rides);

/**
 * @brief Get the average ride statistic between two dates
 *
 * @param rides Rides
 * @param dateA First date
 * @param dateB Second date
 * @param get_func Function to get stat
 * @return Calculated average
 */
double rides_get_avg_stat_in_range(Rides rides, char *dateA, char *dateB,
                                   double (*get_func)(Ride));

/**
 * @brief Get rides with tip
 *
 * @param rides Rides to filter
 * @return Rides with tips
 */
Rides rides_get_rides_with_tip(Rides rides);

/**
 * @brief Get rides with tip between two date
 *
 * @param rides Rides to process
 * @param dateA First date
 * @param dateB Second date
 * @return Rides with tip bewtween two date
 */
Rides rides_get_rides_with_tip_in_range(Rides rides, char *dateA, char *dateB);

#endif
