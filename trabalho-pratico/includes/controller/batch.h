#ifndef __BATCH_H__
#define __BATCH_H__

#include <stdio.h>

typedef struct inputs *Inputs;
typedef struct catalog *Catalog;

/**
 * @brief Run queries in batch
 *
 * @param path_inputs Path to inputs directory
 * @param path_queries Path to queries batch file
 * @return int Control integer
 */
int batch(char *path_inputs, char *path_queries);

/**
 * @brief
 *
 * @param c
 * @return int
 */
int parse_queries_batch(Catalog c);

#endif
