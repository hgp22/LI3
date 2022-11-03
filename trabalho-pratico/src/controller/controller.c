#include "controller.h"
#include "catalog.h"
#include "db.h"
#include "driver.h"
#include "query2.h"
#include "query3.h"
#include "ui.h"
#include "user.h"
#include <stdio.h>
#include <string.h>

#include <glib.h>

int run_controller(char *path_inputs, char *path_queries)
{
    Catalog c = new_catalog();
    load_db(c, path_inputs);
    process_catalog(c);

    FILE *file_queries = freopen(path_queries, "r", stdin);

    run_queries(c);

    fclose(file_queries);

    free_catalog(c);

    return 0;
}

int run_queries(Catalog c)
{
    char *query = NULL;
    size_t len = 0;

    while (getline(&query, &len, stdin) != -1) {
        parse_query(c, query);
    }

    free(query);

    return 0;
}

int parse_query(Catalog c, char *query)
{
    int N;
    switch (query[0]) {
        case '1':
            char id[64];
            sscanf(query, "%*d %s\n", id);
            // If User and Driver could be generalized to Person
            // we could simply do show_query1(query1(c, id))
            // where query1 returns and show_query1 receives a Person
            char *endptr;
            long driver = strtol(id, &endptr, 10);
            if (*endptr != '\0') {
                User u = get_catalog_user(c, id);
                show_query1_user(u);
                free_user(u);
            }
            else {
                Driver d = get_catalog_driver(c, driver);
                show_query1_driver(d);
                free_driver(d);
            }
            break;
        case '2':
            sscanf(query, "%*d %d", &N);
            Query2 q2 = get_catalog_top_n_drivers_by_score(c, N);
            show_query2(q2);
            free_query2_full(q2);
            break;
        case '3':
            sscanf(query, "%*d %d", &N);
            Query3 q3 = get_catalog_top_n_users_by_distance(c, N);
            show_query3(q3);
            free_query3_full(q3);
            break;
        case '4':
            printf("Query 4\n");
            break;
        case '5':
            printf("Query 5\n");
            break;
        case '6':
            printf("Query 6\n");
            break;
        case '7':
            printf("Query 7\n");
            break;
        case '8':
            printf("Query 8\n");
            break;
        case '9':
            printf("Query 9\n");
            break;
    }

    return 0;
}
