#ifndef __UTILS_H__
#define __UTILS_H__

#include <glib.h>

/**
 * @brief
 *
 * @param a
 * @param b
 * @return gint
 */
gint compare_trips(gconstpointer a, gconstpointer b);

/**
 * @brief
 *
 * @param date
 * @return unsigned short
 */
unsigned short date_to_days(char *date);

#endif
