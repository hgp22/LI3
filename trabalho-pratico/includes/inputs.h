#ifndef __INPUTS_H__
#define __INPUTS_H__

#include "drivers.h"
#include "rides.h"
#include "users.h"
#include <stdio.h>

typedef struct inputs *Inputs;

/**
 * @brief Get the input file pointers object
 *
 * @param path_inputs String with path to inputs directory
 * @return Inputs Struct with inputs file pointers
 */
Inputs init_inputs(char *path_inputs);

/**
 * @brief Close inputs file pointers
 *
 * @param input Struct with inputs file pointers
 */
void close_inputs(Inputs input);

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
 * @brief Get the file pointer object
 *
 * @param path_inputs String with path do inputs directory
 * @param input_file Input file name
 * @return FILE* File pointer to input file
 */
static FILE *_get_file_pointer(char *path_inputs, char *input_file);

#endif
