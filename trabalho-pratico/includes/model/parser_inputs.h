#ifndef __PARSER_INPUTS_H__
#define __PARSER_INPUTS_H__

#include <glib.h>
#include <stdio.h>

typedef GHashTable *Users;
typedef GHashTable *Drivers;
typedef GSList *Rides;

/**
 * @brief
 *
 * @param fp
 * @return Users
 */
Users parse_users(FILE *fp);

/**
 * @brief
 *
 * @param fp
 * @return Drivers
 */
Drivers parse_drivers(FILE *fp);

/**
 * @brief
 *
 * @param fp
 * @return Rider
 */
Rides parse_rides(FILE *fp);

#endif
