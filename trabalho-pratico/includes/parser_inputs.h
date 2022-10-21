#ifndef __PARSER_INPUTS_H__
#define __PARSER_INPUTS_H__

#include "batch.h"
#include "catalog.h"
#include "driver.h"
#include "ride.h"
#include "user.h"
#include <glib.h>
#include <stdio.h>

/**
 * @brief
 *
 * @param input
 * @return Catalog*
 */
Catalog *parse_inputs(Inputs *input);

/**
 * @brief
 *
 * @param fp
 * @return GSList*
 */
GSList *parse_users(FILE *fp);

/**
 * @brief
 *
 * @param fp
 * @return GSList*
 */
GSList *parse_drivers(FILE *fp);

/**
 * @brief
 *
 * @param fp
 * @return GSList*
 */
GSList *parse_rides(FILE *fp);

#endif
