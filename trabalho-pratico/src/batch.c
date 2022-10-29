#include "batch.h"
#include "catalog.h"
#include "inputs.h"
#include "parser_inputs.h"
#include "parser_query.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int batch(char *path_inputs, char *path_queries)
{
    Inputs inputs = init_inputs(path_inputs);

    Catalog catalog = init_catalog(inputs);

    close_inputs(inputs);

    FILE *file_queries = freopen(path_queries, "r", stdin);

    parse_queries_batch(catalog);

    fclose(file_queries);

    free_catalog(catalog);

    return 0;
}

int parse_queries_batch(Catalog c)
{
    char *query = NULL;
    size_t len = 0;

    while (getline(&query, &len, stdin) != -1) {
        parse_query(c, query);
    }

    free(query);

    return 0;
}
