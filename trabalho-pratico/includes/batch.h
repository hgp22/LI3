#ifndef __BATCH_H__
#define __BATCH_H__

#include <stdio.h>

typedef struct inputs {
    FILE *file_users;
    FILE *file_drivers;
    FILE *file_rides;
} Inputs;

/**
 * @brief 
 * 
 * @param path_inputs 
 * @param path_queries 
 * @return int 
 */
int batch(char *path_inputs, char *path_queries);

/**
 * @brief Get the input file pointers object
 * 
 * @param path_inputs 
 * @return Inputs 
 */
Inputs *get_input_file_pointers(char *path_inputs);

/**
 * @brief Get the file pointer object
 * 
 * @param path_inputs 
 * @param input_file 
 * @return FILE* 
 */
FILE *get_file_pointer(char *path_inputs, char *input_file);

/**
 * @brief 
 * 
 * @param input 
 */
void close_input_files(Inputs *input);

/**
 * @brief 
 * 
 * @param file_queries 
 * @return int 
 */
int parse_queries_batch(FILE *file_queries);

/**
 * @brief 
 * 
 * @param query 
 * @return int 
 */
int parse_query(char *query);

#endif
