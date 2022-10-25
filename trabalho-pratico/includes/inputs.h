#ifndef __INPUTS_H__
#define __INPUTS_H__

#include "drivers.h"
#include "rides.h"
#include "users.h"
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
 * @brief Get the inputs users object
 * 
 * @param i 
 * @return FILE* 
 */
FILE *get_inputs_users(Inputs i);

/**
 * @brief Get the inputs drivers object
 * 
 * @param i 
 * @return FILE* 
 */
FILE *get_inputs_drivers(Inputs i);

/**
 * @brief Get the inputs rides object
 * 
 * @param i 
 * @return FILE* 
 */
FILE *get_inputs_rides(Inputs i);

/**
 * @brief
 *
 * @param input
 */
void close_inputs(Inputs input);

#endif
