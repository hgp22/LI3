#ifndef __PARSER_INPUTS_H__
#define __PARSER_INPUTS_H__

#include "batch.h"
#include "catalog.h"
#include "driver.h"
#include "drivers.h"
#include "ride.h"
#include "rides.h"
#include "user.h"
#include "users.h"
#include <glib.h>
#include <stdio.h>

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
