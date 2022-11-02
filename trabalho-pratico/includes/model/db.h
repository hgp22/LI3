#ifndef __DB_H__
#define __DB_H__

typedef struct catalog *Catalog;

/**
 * @brief
 *
 * @param c
 * @param path_inputs
 * @return int
 */
int load_db(Catalog c, char *path_inputs);

#endif
