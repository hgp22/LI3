#include "parser_query.h"
#include "catalog.h"
#include "query1.h"
#include <glib.h>
#include <stdio.h>

int parse_query(Catalog c, char *query)
{
    switch (query[0]) {
        case '1':
            char user[64];
            sscanf(query, "%*d %s\n", user);

            char *endptr;
            long driver = strtol(user, &endptr, 10);

            if (*endptr != '\0') {
                User u = g_hash_table_lookup(get_catalog_users(c), user);
                printf("%s\n", user_to_q1_string(u));
            }
            else {
                Driver d = g_hash_table_lookup(get_catalog_drivers(c), &driver);
                printf("%s\n", driver_to_q1_string(d));
            }
            break;
        case '2':
            printf("Query 2\n");
            break;
        case '3':
            printf("Query 3\n");
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
