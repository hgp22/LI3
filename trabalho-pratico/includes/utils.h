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
 * @brief
 *
 * @param date
 * @return unsigned short
 */
unsigned short date_to_days(char *date);

/**
 * @brief
 *
 * @param date
 * @return uint8_t
 */
uint8_t date_to_age(char *date);

#endif
