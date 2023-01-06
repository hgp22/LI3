#ifndef __DATE_H__
#define __DATE_H__

#include <glib.h>

/**
 * @brief Convert a date in the format "dd/mm/yyyy" to the number of days since
 * 01/01/1970.
 *
 * @param date A string containing the date in the format "dd/mm/yyyy".
 * @return The number of days since 01/01/1970.
 */
guint16 date_to_days(const char *date);

/**
 * @brief Converts a number of days since 01/01/1970 to a civil date
 *
 * @param days Days to convert
 * @return Civil date
 */
char *days_to_date(guint16 days);

/**
 * @brief
 *
 * @param date
 * @return guint8
 */
guint8 date_to_age(const char *date);

#endif
