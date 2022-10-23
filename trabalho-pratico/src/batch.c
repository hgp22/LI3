#include "batch.h"
#include "catalog.h"
#include "driver.h"
#include "inputs.h"
#include "parser_inputs.h"
#include "parser_query.h"
#include "ride.h"
#include "user.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int batch(char *path_inputs, char *path_queries)
{
    Inputs inputs = init_inputs(path_inputs);

    Catalog catalog = parse_inputs(inputs);

    close_inputs(inputs);

    printf("Users list length: %d\n",
           g_slist_length(get_catalog_users(catalog)));
    printf("Drivers list length: %d\n",
           g_slist_length(get_catalog_drivers(catalog)));
    printf("Rides list length: %d\n",
           g_slist_length(get_catalog_rides(catalog)));

    // TODO: generate final catalog

    free_catalog(catalog);

    FILE *file_queries = freopen(path_queries, "r", stdin);

    parse_queries_batch();

    fclose(file_queries);

    return 0;
}

int parse_queries_batch()
{
    char *query = NULL;
    size_t len = 0;

    while (getline(&query, &len, stdin) != -1) {
        parse_query(query);
    }

    free(query);

    return 0;
}
