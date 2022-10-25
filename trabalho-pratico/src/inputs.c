#include "inputs.h"
#include "catalog.h"
#include "parser_inputs.h"
#include <glib.h>
#include <stdio.h>

struct inputs {
    FILE *file_users;
    FILE *file_drivers;
    FILE *file_rides;
};

/**
 * @brief Get the file pointer object
 *
 * @param path_inputs
 * @param input_file
 * @return FILE*
 */
static FILE *_get_file_pointer(char *path_inputs, char *input_file);

Inputs init_inputs(char *path_inputs)
{
    // ? how to handle "./" and "/" before and after path_inputs

    Inputs inputs = g_new(struct inputs, 1);

    inputs->file_users = _get_file_pointer(path_inputs, "/users.csv");
    inputs->file_drivers = _get_file_pointer(path_inputs, "/drivers.csv");
    inputs->file_rides = _get_file_pointer(path_inputs, "/rides.csv");

    return inputs;
}

static FILE *_get_file_pointer(char *path_inputs, char *input_file)
{
    char *path_file =
        malloc((strlen(path_inputs) + strlen(input_file) + 1) * sizeof(char));
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

Catalog parse_inputs(Inputs input)
{
    Catalog catalog = init_catalog();

    set_catalog_users(catalog, parse_users(input->file_users));
    set_catalog_drivers(catalog, parse_drivers(input->file_drivers));
    set_catalog_rides(catalog, parse_rides(input->file_rides));

    return catalog;
}

void close_inputs(Inputs i)
{
    fclose(i->file_users);
    fclose(i->file_drivers);
    fclose(i->file_rides);
    free(i);
}
