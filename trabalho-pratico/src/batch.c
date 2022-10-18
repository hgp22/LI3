#include "batch.h"
#include "parser_query.h"
#include "parser_inputs.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int batch(char *path_inputs, char *path_queries)
{
    Inputs *input = get_input_file_pointers(path_inputs);

    parse_inputs(input);

    close_input_files(input);

    // TODO: generate catalog

    FILE *file_queries = fopen(path_queries, "r");

    parse_queries_batch(file_queries);

    fclose(file_queries);

    return 0;
}

Inputs *get_input_file_pointers(char *path_inputs)
{
    // ? how to handle "./" and "/" before and after path_inputs
    FILE *file_users = get_file_pointer(path_inputs, "/users.csv");
    FILE *file_drivers = get_file_pointer(path_inputs, "/drivers.csv");
    FILE *file_rides = get_file_pointer(path_inputs, "/rides.csv");

    Inputs *inputs = g_new(Inputs, 1);

    inputs->file_users = file_users;
    inputs->file_drivers = file_drivers;
    inputs->file_rides = file_rides;

    return inputs;
}

FILE *get_file_pointer(char *path_inputs, char *input_file)
{
    char *path_file =
        (char *)malloc(strlen(path_inputs) + strlen(input_file) + 1);
    strcpy(path_file, path_inputs);
    strcat(path_file, input_file);

    FILE *fp = fopen(path_file, "r");
    if (fp == NULL) {
        perror(path_file);
        exit(1);
    }

    free(path_file);

    return fp;
}

void close_input_files(Inputs *input)
{
    fclose(input->file_users);
    fclose(input->file_drivers);
    fclose(input->file_rides);
}

int parse_queries_batch(FILE *file_queries)
{
    char *query = NULL;
    size_t len = 0;

    while (getline(&query, &len, file_queries) != -1) {
        parse_query(query);
    }

    free(query);

    return 0;
}
