#ifndef __CONTROLLER_BATCH_H__
#define __CONTROLLER_BATCH_H__

#include <stdio.h>

typedef struct taxi_system *TaxiSystem;

/**
 * @brief Batch main function
 *
 * @param path_inputs Path to inputs directory
 * @param path_queries Path to queries batch file
 * @return int Control integer
 */
int run_batch(const char *path_inputs, const char *path_queries);

/**
 * @brief
 *
 * @param ts
 * @param query
 * @param fp
 * @return int
 */
int run_query(const TaxiSystem ts, const char *query, FILE *fp);

#endif
