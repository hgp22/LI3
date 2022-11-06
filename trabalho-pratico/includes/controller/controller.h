#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

typedef struct catalog *Catalog;

/**
 * @brief Run queries in batch
 *
 * @param path_inputs Path to inputs directory
 * @param path_queries Path to queries batch file
 * @return int Control integer
 */
int run_controller(char *path_inputs, char *path_queries);

/**
 * @brief
 *
 * @param c
 * @return int
 */
int run_queries(Catalog c);

/**
 * @brief
 *
 * @param c
 * @param query
 * @return int
 */
int parse_query(Catalog c, char *query);

#endif
