#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

typedef struct catalog *Catalog;

/**
 * @brief Controller main function
 *
 * @param path_inputs Path to inputs directory
 * @param path_queries Path to queries batch file
 * @return int Control integer
 */
int run_controller(char *path_inputs, char *path_queries);

/**
 * @brief Controller loop, runs each query
 *
 * @param c Complete catalog
 * @return int Control integer
 */
int run_queries(Catalog c);

/**
 * @brief Runs a single query
 *
 * @param c Complete catalog
 * @param query Query to be runned
 * @return int Control integer
 */
int run_query(Catalog c, char *query);

#endif
