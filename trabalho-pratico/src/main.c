#include <stdio.h>
#include <glib.h>
#include "config.h"
#include "parser.h"

int main(int argc, char **argv)
{
    FILE *fd = fopen("./datasets/dataset_fase1/drivers.csv", "r");

    GSList *drivers = NULL;

    drivers = parse_drivers(fd, drivers);

    printf("Drivers list length: %d\n", g_slist_length(drivers));
    printf("First driver added: %s\n", ((Driver*)drivers->data)->name);
    printf("Last driver added: %s\n", ((Driver*)g_slist_last(drivers)->data)->name);

    fclose(fd);

    g_slist_free(drivers);

    return 0;
}
