#include "parser_query.h"
#include <stdio.h>

int parse_query(char *query)
{
    switch (query[0]) {
        case '1':
            printf("Query 1\n");
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
