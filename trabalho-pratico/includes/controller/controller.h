#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

/**
 * @brief Controller main function
 *
 * @param path_inputs Path to inputs directory
 * @param path_queries Path to queries batch file
 * @return int Control integer
 */
int run_controller(const char *path_inputs, const char *path_queries);

#endif
