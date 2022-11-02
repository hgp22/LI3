#include "parser_query.h"
#include "catalog.h"
#include "query1.h"
#include "query2.h"
#include "query3.h"
#include <stdio.h>

int counter = 1;

int parse_query(Catalog c, char *query)
{
    int N;
    switch (query[0]) {
        case '1':
            char id[64];
            sscanf(query, "%*d %s\n", id);
            query1(c, id);
            break;
        case '2':
            sscanf(query, "%*d %d", &N);
            query2(c, N);
            break;
        case '3':
            sscanf(query, "%*d %d", &N);
            query3(c, N);
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
