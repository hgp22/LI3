#include "loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *load_file(const char *inputs_path, char *input_file, void *collection,
                void (*load_record)(void *, char *))
{
    char *input_file_path =
        malloc((strlen(inputs_path) + strlen(input_file) + 1) *
               sizeof(*input_file_path));
    strcpy(input_file_path, inputs_path);
    strcat(input_file_path, input_file);

    FILE *fp = fopen(input_file_path, "r");
    if (fp == NULL) {
        perror(input_file_path);
        exit(1);
    }

    free(input_file_path);

    char *line = NULL;
    size_t len = 0;

    getline(&line, &len, fp); // Remove header

    while (getline(&line, &len, fp) != -1) {
        load_record(collection, line);
    }

    free(line);
    fclose(fp);

    return collection;
}
