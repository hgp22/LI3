#include "parser_query.h"
#include "catalog.h"
#include "driver.h"
#include "query1.h"
#include "user.h"
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
                if (u != NULL && get_user_account_status(u)) {
                    char *q1_answer = user_to_q1_string(u);
                    printf("%s\n", q1_answer);
                    free(q1_answer);
                }
            }
            else {
                Driver d = g_hash_table_lookup(get_catalog_drivers(c), &driver);
                if (d != NULL && get_driver_account_status(d)) {
                    char *q1_answer = driver_to_q1_string(d);
                    printf("%s\n", q1_answer);
                    free(q1_answer);
                }
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
