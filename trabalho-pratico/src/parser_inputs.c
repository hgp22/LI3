#include "parse_inputs.h"

int parse_inputs(Inputs *input) {
    GSList *drivers = NULL;

    drivers = parse_drivers(fd, drivers);

    printf("Drivers list length: %d\n", g_slist_length(drivers));
    printf("First driver added: %s\n", ((Driver*)drivers->data)->name);
    printf("Last driver added: %s\n", ((Driver*)g_slist_last(drivers)->data)->name);

    fclose(fd);

    g_slist_free(drivers);

    return 0;
}