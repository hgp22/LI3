#ifndef __PARSER_INPUTS_H__
#define __PARSER_INPUTS_H__

#include "batch.h"
#include "catalog.h"
#include "config.h"
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
 * @param fu
 * @return GSList*
 */
GSList *parse_users(FILE *fu);

/**
 * @brief
 *
 * @param fd
 * @return GSList*
 */
GSList *parse_drivers(FILE *fd);

/**
 * @brief
 *
 * @param fr
 * @return GSList*
 */
GSList *parse_rides(FILE *fr);

#endif
