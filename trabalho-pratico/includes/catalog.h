#ifndef __CATALOG_H__
#define __CATALOG_H__

#include <glib.h>

typedef struct catalog {
    GSList *users;
    GSList *drivers;
    GSList *rides;
} Catalog;

/**
 * @brief
 *
 * @param catalog
 */
void free_catalog(Catalog *catalog);

#endif
