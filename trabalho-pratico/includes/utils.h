#ifndef __UTILS_H__
#define __UTILS_H__

#include <glib.h>
#include <stdint.h>

/**
 * @brief
 *
 * @param a
 * @param b
 * @return gint
 */
gint compare_trips(gpointer a, gpointer b);

/**
 * @brief Converts a civil date to the number of days since 01/01/1970
 *
 * @param date Date to convert
 * @return Number of days
 */
unsigned short date_to_days(char *date);

/**
 * @brief Converts a number of days since 01/01/1970 to a civil date
 *
 * @param days Days to convert
 * @return Civil date
 */
char *days_to_date(unsigned short days);

/**
 * @brief
 *
 * @param date
 * @return uint8_t
 */
uint8_t date_to_age(char *date);

#endif
