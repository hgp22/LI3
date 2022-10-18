#ifndef __BATCH_H__
#define __BATCH_H__

#include "config.h"
#include <stdio.h>

typedef struct inputs {
    FILE *file_users;
    FILE *file_drivers;
    FILE *file_rides;
} Inputs;

/**
 * @brief Run queries in batch
 *
 * @param path_inputs Path to inputs directory
 * @param path_queries Path to queries batch file
 * @return int Control integer
 */
int batch(char *path_inputs, char *path_queries);

/**
 * @brief Get the input file pointers object
 *
 * @param path_inputs String with path to inputs directory
 * @return Inputs Struct with inputs file pointers
 */
Inputs *get_input_file_pointers(char *path_inputs);

/**
 * @brief Get the file pointer object
 *
 * @param path_inputs String with path do inputs directory
 * @param input_file Input file name
 * @return FILE* File pointer to input file
 */
FILE *get_file_pointer(char *path_inputs, char *input_file);

/**
 * @brief Close inputs file pointers
 *
 * @param input Struct with inputs file pointers
 */
void close_input_files(Inputs *input);

/**
 * @brief Parse queries in queries batch file
 *
 * @return int Control integer
 */
int parse_queries_batch(void);

#endif
