#ifndef __INPUTS_H__
#define __INPUTS_H__

#include "catalog.h"
#include <stdio.h>

typedef struct inputs *Inputs;

/**
 * @brief
 *
 * @param path_inputs
 * @return Inputs
 */
Inputs init_inputs(char *path_inputs);

/**
 * @brief
 *
 * @param input
 * @return Catalog
 */
Catalog parse_inputs(Inputs input);

/**
 * @brief
 *
 * @param input
 */
void close_inputs(Inputs input);

#endif
