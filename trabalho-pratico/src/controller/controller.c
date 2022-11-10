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

int run_controller(char *path_inputs, char *path_queries)
{
    Catalog c = catalog_new();
    db_load(c, path_inputs);
    catalog_process(c);

    FILE *file_queries = freopen(path_queries, "r", stdin);

    run_queries(c);

    fclose(file_queries);

    catalog_free(c);

    return 0;
}

int run_queries(Catalog c)
{
    char *query = NULL;
    size_t len = 0;
    FILE *fp = NULL;

    while (getline(&query, &len, stdin) != -1) {
        fp = next_output_file();
        run_query(c, query);
    }

    fclose(fp);
    free(query);

    return 0;
}

int run_query(Catalog c, char *query)
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
                User u = catalog_get_user(c, id);
                show_query1_user(u);
                user_free(u);
            }
            else {
                Driver d = catalog_get_driver(c, driver);
                show_query1_driver(d);
                driver_free(d);
            }
            break;
        case '2':
            sscanf(query, "%*d %d", &N);
            Query2 q2 = catalog_get_top_n_drivers_by_score(c, N);
            show_query2(q2);
            query2_free(q2);
            break;
        case '3':
            sscanf(query, "%*d %d", &N);
            Query3 q3 = catalog_get_top_n_users_by_distance(c, N);
            show_query3(q3);
            query3_free(q3);
            break;
        case '4':
            char city[64];
            sscanf(query, "%*d %s", city);
            show_query4(catalog_get_city_avg_cost(c, city));
            break;
        case '5':
            char dateA[16];
            char dateB[16];
            sscanf(query, "%*d %s %s", dateA, dateB);
            show_query5(catalog_get_avg_cost_in_range(c, dateA, dateB));
            break;
        case '6':
            char city1[64];
            char dateA1[16];
            char dateB1[16];
            sscanf(query, "%*d %s %s %s", city1, dateA1, dateB1);
            show_query6(
                catalog_get_city_avg_dist_in_range(c, city1, dateA1, dateB1));
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
