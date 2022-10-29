#include "inputs.h"
#include "drivers.h"
#include "parser_inputs.h"
#include "rides.h"
#include "users.h"
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
 * @param path_inputs String with path do inputs directory
 * @param input_file Input file name
 * @return FILE* File pointer to input file
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

void close_inputs(Inputs i)
{
    fclose(i->file_users);
    fclose(i->file_drivers);
    fclose(i->file_rides);
    free(i);
}

FILE *get_inputs_users(Inputs i)
{
    return i->file_users;
}

FILE *get_inputs_drivers(Inputs i)
{
    return i->file_drivers;
}

FILE *get_inputs_rides(Inputs i)
{
    return i->file_rides;
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
