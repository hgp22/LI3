#ifndef __DB_H__
#define __DB_H__

typedef struct catalog *Catalog;

/**
 * @brief Loads inputs files to Catalog
 *
 * @param c Catalog to be loaded to
 * @param path_inputs Path to inputs
 * @return Control integer
 */
int db_load(Catalog c, char *path_inputs);

#endif
