#include "batch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int batch(char *path_inputs, char *path_queries) {
    // ? how to handle "./" and "/" before and after path_inputs
    // ? are there better optoins to create the complete path string
    // TODO: move to function and reuse in interactive mode
    char *path_users = strcat(strdup(path_inputs), "/users.csv");
    char *path_drivers = strcat(strdup(path_inputs), "/drivers.csv");
    char *path_rides = strcat(strdup(path_inputs), "/rides.csv");

    FILE *file_users = fopen(path_users, "r");
    if (file_users == NULL) {
        perror(path_users);
        return 1;
    }
    FILE *file_drivers = fopen(path_drivers, "r");
    if (file_drivers == NULL) {
        perror(path_drivers);
        return 1;
    }
    FILE *file_rides = fopen(path_rides, "r");
    if (file_rides == NULL) {
        perror(path_rides);
        return 1;
    }

    free(path_users);
    free(path_drivers);
    free(path_rides);

    // parse inputs
    // generate catalog

    fclose(file_users);
    fclose(file_drivers);
    fclose(file_rides);

    char *query = NULL;
    size_t len = 0;
    FILE *file_queries = fopen(path_queries, "r");

    while (getline(&query, &len, file_queries) != -1) {
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
    }

    free(query);
    fclose(file_queries);

    return 0;
}